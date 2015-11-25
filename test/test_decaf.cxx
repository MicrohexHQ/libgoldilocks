/**
 * @file test_decaf.cxx
 * @author Mike Hamburg
 *
 * @copyright
 *   Copyright (c) 2015 Cryptography Research, Inc.  \n
 *   Released under the MIT License.  See LICENSE.txt for license information.
 *
 * @brief C++ tests, because that's easier.
 */

#include <decaf.hxx>
#include <decaf/shake.hxx>
#include <decaf/crypto.h>
#include <decaf/crypto.hxx>
#include <stdio.h>

using namespace decaf;

static bool passing = true;
static const long NTESTS = 10000;

class Test {
public:
    bool passing_now;
    Test(const char *test) {
        passing_now = true;
        printf("%s...", test);
        if (strlen(test) < 27) printf("%*s",int(27-strlen(test)),"");
        fflush(stdout);
    }
    ~Test() {
        if (std::uncaught_exception()) {
            fail();
            printf("  due to uncaught exception.\n");
        }
        if (passing_now) printf("[PASS]\n");
    }
    void fail() {
        if (!passing_now) return;
        passing_now = passing = false;
        printf("[FAIL]\n");
    }
};

template<typename Group> struct Tests {

typedef typename Group::Scalar Scalar;
typedef typename Group::Point Point;
typedef typename Group::Precomputed Precomputed;

static void print(const char *name, const Scalar &x) {
    unsigned char buffer[Scalar::SER_BYTES];
    x.serializeInto(buffer);
    printf("  %s = 0x", name);
    for (int i=sizeof(buffer)-1; i>=0; i--) {
        printf("%02x", buffer[i]);
    }
    printf("\n");
}

static void hexprint(const char *name, const SecureBuffer &buffer) {
    printf("  %s = 0x", name);
    for (int i=buffer.size()-1; i>=0; i--) {
        printf("%02x", buffer[i]);
    }
    printf("\n");
}

static void print(const char *name, const Point &x) {
    unsigned char buffer[Point::SER_BYTES];
    x.serializeInto(buffer);
    printf("  %s = 0x", name);
    for (int i=Point::SER_BYTES-1; i>=0; i--) {
        printf("%02x", buffer[i]);
    }
    printf("\n");
}

static bool arith_check(
    Test &test,
    const Scalar &x,
    const Scalar &y,
    const Scalar &z,
    const Scalar &l,
    const Scalar &r,
    const char *name
) {
    if (l == r) return true;
    test.fail();
    printf("  %s", name);
    print("x", x);
    print("y", y);
    print("z", z);
    print("lhs", l);
    print("rhs", r);
    return false;
}

static bool point_check(
    Test &test,
    const Point &p,
    const Point &q,
    const Point &R,
    const Scalar &x,
    const Scalar &y,
    const Point &l,
    const Point &r,
    const char *name
) {
    bool good = l==r;
    if (!p.validate()) { good = false; printf("  p invalid\n"); }
    if (!q.validate()) { good = false; printf("  q invalid\n"); }
    if (!r.validate()) { good = false; printf("  r invalid\n"); }
    if (!l.validate()) { good = false; printf("  l invalid\n"); }
    if (good) return true;
    
    test.fail();
    printf("  %s", name);
    print("x", x);
    print("y", y);
    print("p", p);
    print("q", q);
    print("r", R);
    print("lhs", r);
    print("rhs", l);
    return false;
}

static void test_arithmetic() {
    SpongeRng rng(Block("test_arithmetic"));
    
    Test test("Arithmetic");
    Scalar x(0),y(0),z(0);
    arith_check(test,x,y,z,INT_MAX,(decaf_word_t)INT_MAX,"cast from max");
    arith_check(test,x,y,z,INT_MIN,-Scalar(1+(decaf_word_t)INT_MAX),"cast from min");
        
    for (int i=0; i<NTESTS*10 && test.passing_now; i++) {
        /* TODO: pathological cases */
        size_t sob = DECAF_255_SCALAR_BYTES + 8 - (i%16);
        Scalar x(rng.read(sob));
        Scalar y(rng.read(sob));
        Scalar z(rng.read(sob));
        

        arith_check(test,x,y,z,x+y,y+x,"commute add");
        arith_check(test,x,y,z,x,x+0,"ident add");
        arith_check(test,x,y,z,x,x-0,"ident sub");
        arith_check(test,x,y,z,x+(y+z),(x+y)+z,"assoc add");
        arith_check(test,x,y,z,x*(y+z),x*y + x*z,"distributive mul/add");
        arith_check(test,x,y,z,x*(y-z),x*y - x*z,"distributive mul/add");
        arith_check(test,x,y,z,x*(y*z),(x*y)*z,"assoc mul");
        arith_check(test,x,y,z,x*y,y*x,"commute mul");
        arith_check(test,x,y,z,x,x*1,"ident mul");
        arith_check(test,x,y,z,0,x*0,"mul by 0");
        arith_check(test,x,y,z,-x,x*-1,"mul by -1");
        arith_check(test,x,y,z,x+x,x*2,"mul by 2");
        
        if (i%20) continue;
        if (y!=0) arith_check(test,x,y,z,x*y/y,x,"invert");
        try {
            y = x/0;
            test.fail();
            printf("  Inverted zero!");
            print("x", x);
            print("y", y);
        } catch(CryptoException) {}
    }
}

static void test_elligator() {
    SpongeRng rng(Block("test_elligator"));
    Test test("Elligator");
    
    const int NHINTS = Group::REMOVED_COFACTOR * 2;
    SecureBuffer *alts[NHINTS];
    bool successes[NHINTS];
    SecureBuffer *alts2[NHINTS];
    bool successes2[NHINTS];

    for (int i=0; i<NTESTS/10 && (test.passing_now || i < 100); i++) {
        size_t len =  (i % (2*Point::HASH_BYTES + 3));
        SecureBuffer b1(len);
        if (i!=Point::HASH_BYTES) rng.read(b1); /* special test case */
        if (i==1) b1[0] = 1; /* special case test */
        if (len >= Point::HASH_BYTES) b1[Point::HASH_BYTES-1] &= 0x7F; // FIXME MAGIC
        
        Point s = Point::from_hash(b1), ss=s;
        for (int j=0; j<(i&3); j++) ss = ss.debugging_torque();
        
        ss = ss.debugging_pscale(rng);
        
        bool good = false;
        for (int j=0; j<NHINTS; j++) {
            alts[j] = new SecureBuffer(len);
            alts2[j] = new SecureBuffer(len);

            if (len > Point::HASH_BYTES)
                memcpy(&(*alts[j])[Point::HASH_BYTES], &b1[Point::HASH_BYTES], len-Point::HASH_BYTES);
            
            if (len > Point::HASH_BYTES)
                memcpy(&(*alts2[j])[Point::HASH_BYTES], &b1[Point::HASH_BYTES], len-Point::HASH_BYTES);
            
            successes[j]  = decaf_successful( s.invert_elligator(*alts[j], j));
            successes2[j] = decaf_successful(ss.invert_elligator(*alts2[j],j));
            
            if (successes[j] != successes2[j]
                || (successes[j] && successes2[j] && *alts[j] != *alts2[j])
            ) {
                test.fail();
                printf("   Unscalable Elligator inversion: i=%d, hint=%d, s=%d,%d\n",i,j,
                    -int(successes[j]),-int(successes2[j]));
                hexprint("x",b1);
                hexprint("X",*alts[j]);
                hexprint("X",*alts2[j]);
            }
           
            if (successes[j]) {
                good = good || (b1 == *alts[j]);
                for (int k=0; k<j; k++) {
                    if (successes[k] && *alts[j] == *alts[k]) {
                        test.fail();
                        printf("   Duplicate Elligator inversion: i=%d, hints=%d, %d\n",i,j,k);
                        hexprint("x",b1);
                        hexprint("X",*alts[j]);
                    }
                }
                if (s != Point::from_hash(*alts[j])) {
                    test.fail();
                    printf("   Fail Elligator inversion round-trip: i=%d, hint=%d %s\n",i,j,
                        (s==-Point::from_hash(*alts[j])) ? "[output was -input]": "");
                    hexprint("x",b1);
                    hexprint("X",*alts[j]);
                }
            }
        }
        
        if (!good) {
            test.fail();
            printf("   %s Elligator inversion: i=%d\n",good ? "Passed" : "Failed", i);
            hexprint("B", b1);
            for (int j=0; j<NHINTS; j++) {
                printf("  %d: %s%s", j, successes[j] ? "succ" : "fail\n", (successes[j] && *alts[j] == b1) ? " [x]" : "");
                if (successes[j]) {
                    hexprint("b", *alts[j]);
                }
            }
            printf("\n");
        }
        
        for (int j=0; j<NHINTS; j++) {
            delete alts[j];
            alts[j] = NULL;
            delete alts2[j];
            alts2[j] = NULL;
        }
        
        Point t(rng);
        point_check(test,t,t,t,0,0,t,Point::from_hash(t.steg_encode(rng)),"steg round-trip");
        
        
        
        
    }
}

static void test_ec() {
    SpongeRng rng(Block("test_ec"));
    
    Test test("EC");

    Point id = Point::identity(), base = Point::base();
    point_check(test,id,id,id,0,0,Point::from_hash(""),id,"fh0");
    
    if (Group::FIELD_MODULUS_TYPE == 3) {
        /* When p == 3 mod 4, the QNR is -1, so u*1^2 = -1 also produces the
         * identity.
         */
        point_check(test,id,id,id,0,0,Point::from_hash("\x01"),id,"fh1");
    }
    
    for (int i=0; i<NTESTS && test.passing_now; i++) {
        /* TODO: pathological cases */
        Scalar x(rng);
        Scalar y(rng);
        Point p(rng);
        Point q(rng);
        
        Point d1, d2;
        
        SecureBuffer buffer(2*Point::HASH_BYTES);
        rng.read(buffer);
        Point r = Point::from_hash(buffer);
        
        point_check(test,p,q,r,0,0,p,Point(p.serialize()),"round-trip");
        Point pp = p.debugging_torque().debugging_pscale(rng);
        if (!memeq(pp.serialize(),p.serialize())) {
            test.fail();
            printf("Fail torque seq test\n");
        }
        point_check(test,p,q,r,0,0,p,pp,"torque eq");
        point_check(test,p,q,r,0,0,p+q,q+p,"commute add");
        point_check(test,p,q,r,0,0,(p-q)+q,p,"correct sub");
        point_check(test,p,q,r,0,0,p+(q+r),(p+q)+r,"assoc add");
        point_check(test,p,q,r,0,0,p.times_two(),p+p,"dbl add");
        
        if (i%10) continue;
        point_check(test,p,q,r,x,0,x*(p+q),x*p+x*q,"distr mul");
        point_check(test,p,q,r,x,y,(x*y)*p,x*(y*p),"assoc mul");
        point_check(test,p,q,r,x,y,x*p+y*q,Point::double_scalarmul(x,p,y,q),"double mul");
        
        p.dual_scalarmul(d1,d2,x,y);
        point_check(test,p,q,r,x,y,x*p,d1,"dual mul 1");
        point_check(test,p,q,r,x,y,y*p,d2,"dual mul 2");
        
        point_check(test,base,q,r,x,y,x*base+y*q,q.non_secret_combo_with_base(y,x),"ds vt mul");
        point_check(test,p,q,r,x,0,Precomputed(p)*x,p*x,"precomp mul");
        point_check(test,p,q,r,0,0,r,
            Point::from_hash(Buffer(buffer).slice(0,Point::HASH_BYTES))
            + Point::from_hash(Buffer(buffer).slice(Point::HASH_BYTES,Point::HASH_BYTES)),
            "unih = hash+add"
        );
            
        point_check(test,p,q,r,x,0,Point(x.direct_scalarmul(p.serialize())),x*p,"direct mul");
    }
}

static void test_crypto() {
    Test test("Sample crypto");
    SpongeRng rng(Block("test_decaf_crypto"));

    for (int i=0; i<NTESTS && test.passing_now; i++) {
        PrivateKey<Group> priv1(rng), priv2(rng);
        PublicKey<Group> pub1(priv1), pub2(priv2);
        
        SecureBuffer message = rng.read(i);
        SecureBuffer sig(priv1.sign(message));
        pub1.verify(message, sig);
    }
}

}; // template<GroupId GROUP>

// TODO cross-field
static void test_decaf() {
    Test test("Sample crypto");
    SpongeRng rng(Block("test_decaf"));

    decaf_255_symmetric_key_t proto1,proto2;
    decaf_255_private_key_t s1,s2;
    decaf_255_public_key_t p1,p2;
    decaf_255_signature_t sig;
    unsigned char shared1[1234],shared2[1234];
    const char *message = "Hello, world!";

    for (int i=0; i<NTESTS && test.passing_now; i++) {
        rng.read(Buffer(proto1,sizeof(proto1)));
        rng.read(Buffer(proto2,sizeof(proto2)));
        decaf_255_derive_private_key(s1,proto1);
        decaf_255_private_to_public(p1,s1);
        decaf_255_derive_private_key(s2,proto2);
        decaf_255_private_to_public(p2,s2);
        if (DECAF_SUCCESS != decaf_255_shared_secret (shared1,sizeof(shared1),s1,p2,0)) {
            test.fail(); printf("Fail ss12\n");
        }
        if (DECAF_SUCCESS != decaf_255_shared_secret (shared2,sizeof(shared2),s2,p1,1)) {
            test.fail(); printf("Fail ss21\n");
        }
        if (memcmp(shared1,shared2,sizeof(shared1))) {
            test.fail(); printf("Fail ss21 == ss12\n");   
        }
        decaf_255_sign (sig,s1,(const unsigned char *)message,strlen(message));
        if (DECAF_SUCCESS != decaf_255_verify (sig,p1,(const unsigned char *)message,strlen(message))) {
            test.fail(); printf("Fail sig ver\n");   
        }
    }
}

int main(int argc, char **argv) {
    (void) argc; (void) argv;
    
    printf("Testing %s:\n",IsoEd25519::name());
    Tests<IsoEd25519>::test_arithmetic();
    Tests<IsoEd25519>::test_elligator();
    Tests<IsoEd25519>::test_ec();
    Tests<IsoEd25519>::test_crypto();
    test_decaf();
    
    printf("\n");
    printf("Testing %s:\n", Ed448Goldilocks::name());
    Tests<Ed448Goldilocks>::test_arithmetic();
    Tests<Ed448Goldilocks>::test_elligator();
    Tests<Ed448Goldilocks>::test_ec();
    Tests<Ed448Goldilocks>::test_crypto();
    
    if (passing) printf("Passed all tests.\n");
    
    return passing ? 0 : 1;
}
