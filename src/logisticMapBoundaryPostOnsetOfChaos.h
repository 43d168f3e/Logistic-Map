
#if 0
logisticMapBoundaryPostOnsetOfChaos.h
#include "logisticMapBoundaryPostOnsetOfChaos.h"
#include "src/logisticMapBoundaryPostOnsetOfChaos.h"
#endif


#if !defined(LOGISTICMAPBOUNDARYPOSTONSETOFCHAOS_H_27B82C95YD3898441D9383F44EE6159A9F)
#define LOGISTICMAPBOUNDARYPOSTONSETOFCHAOS_H_27B82C95YD3898441D9383F44EE6159A9F

#include <cstdint>
#include <cmath>
#include <limits>
using dbl_prec = std::numeric_limits< long double > ;
///////////////////////////////////////////////////////////////////////////////
/// std::mt19937 mersenne_twister_engine
///////////////////////////////////////////////////////////////////////////////
//dice_pools.cpp:
//All those includes are just to init the mersenne twister
#include <array>
#include <algorithm>
#include <functional>
#include <random>


static std::mt19937 init_mersenne_twister() {
    std::array<std::uint32_t, std::mt19937::state_size> seed_bits{};
    std::random_device real_random{};
    std::generate(seed_bits.begin(), seed_bits.end(), std::ref(real_random));
    std::seed_seq wrapped_seed_bits(seed_bits.begin(), seed_bits.end());

    return std::mt19937(wrapped_seed_bits);
}

/*
long double is a 64 bit IEEE 754 long double precision Floating Point Number (1 bit for the sign, 11 bits for the exponent, and 52* bits for the value), i.e.
long double has 15 decimal digits of precision.
*/
#if 10
//https://oeis.org/A098587/constant
static const constexpr long double onsetOfChaos_f=3.5699456718709449018420051513864989367638369115148323781079755299213628875001367775263210342163L;
// 0 <= t <= 1  :
static long double rateL(long double t) {return(onsetOfChaos_f + (4.0L-onsetOfChaos_f)*t);};

// onsetOfChaos_f <= R <= 4  :
static long double LogisticMap_Boundary_Max_Post_Onset_Of_Chaos(long double R) {return(R/(4.0L) );};

//onsetOfChaos_f <= R <= 4
static long double LogisticMap_Boundary_Min_Post_Onset_Of_Chaos(long double const R) {
return
0.79653200625688076289790171934909401675520941289850532668L*(4.0L - R) + 0.0051485674792323880177977881243251755194L
*std::cyl_bessel_jl(1,35.639273641330774618773658598626407476725855391054L - 8.9098184103326936546934146496566018691814638477634L*R)
- 0.052788545017881380211789667693960708467L
*std::cyl_bessel_jl(2,47.76719559301384384443880353516776577688497419234L - 11.941798898253460961109700883791941444221243548085L*R)
+ 0.33806834938447983982024332296705373538L
*std::cyl_bessel_jl(3,59.342845576565008465833021435557191408949636375666L - 14.835711394141252116458255358889297852237409093917L*R)
- 1.56188821618486164536834776446411420937L
*std::cyl_bessel_jl(4,70.580314515301118240307967813293685731415156400535L - 17.645078628825279560076991953323421432853789100134L*R)
+ 5.1108252858400804759324523406363187191L
*std::cyl_bessel_jl(5,81.584890486931386088715931632366652084230643959208L - 20.396222621732846522178982908091663021057660989802L*R)
- 11.5649557451486330659124398140464651724L
*std::cyl_bessel_jl(6,92.417249396787427253558682638727633188718923499889L - 23.104312349196856813389670659681908297179730874972L*R)
+ 18.389047999717708062861389770178203804L
*std::cyl_bessel_jl(7,103.11599529739575249266254028805671891937205331999L - 25.778998824348938123165635072014179729843013329998L*R)
- 21.0745095514541202773613374876007676819L
*std::cyl_bessel_jl(8,113.70742219653722022205656282536274272100553751276L - 28.42685554913430505551414070634068568025138437819L*R)
+ 17.0138562906890750008650835244297658039L
*std::cyl_bessel_jl(9,124.21035765907079620356400804878074600105161831367L - 31.052589414767699050891002012195186500262904578418L*R)
- 8.5642574993083246284704182704869976991L
*std::cyl_bessel_jl(10,134.63880946884073721478683273354835387969493030878L - 33.659702367210184303696708183387088469923732577194L*R)
+ 1.96099627337898429566302257451705079956L
*std::cyl_bessel_jl(11,145.00352039035518127903387012663015801963466157128L - 36.250880097588795319758467531657539504908665392821L*R)
+ 0.00015763180165959375627488084255361250515735826535514L
*std::sin(146.102129340599590771028650809431861661599734379220485985L - 36.5255323351498976927571627023579654153999335948051214963L*R)
+ 0.0007917487335465474393219848641213427752081089510726L
*std::sin(87.661277604359754462617190485659116996959840627532291591L - 21.9153194010899386156542976214147792492399601568830728978L*R)
+ 0.021994203867497879870936997817692491285004331733565L
*std::sin(29.2204258681199181542057301618863723323199468758440971971L - 7.3051064670299795385514325404715930830799867189610242993L*R)
;}

#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/// NS_LogisticMap
///////////////////////////////////////////////////////////////////////////////
namespace NS_LogisticMap{
    constexpr const long prec{400};
    static std::mt19937 MERSENNE_TWISTER_RNG = init_mersenne_twister();
    static std::uniform_real_distribution<> dist(0.001, 0.999);
    static std::uniform_real_distribution<long double> distL(0.1, 0.9);
    static std::uniform_real_distribution<double> uniform_real_distribution(0, 1);
    static std::uniform_real_distribution<long double> uniform_real_distributionL(0, 1);
    static double urd(void) {return uniform_real_distribution(NS_LogisticMap::MERSENNE_TWISTER_RNG);}
// onsetOfChaos_f <= R <= 4  :
        static long double urdL(long double const R) {
            long double x1=LogisticMap_Boundary_Max_Post_Onset_Of_Chaos(R);
            long double x0=LogisticMap_Boundary_Min_Post_Onset_Of_Chaos(R);
            return x0+distL(NS_LogisticMap::MERSENNE_TWISTER_RNG)*(x1-x0);}

#define RECORD_LINE_NUMBER00(X) X=__LINE__;
#define RECORD_LINE_NUMBER(X) RECORD_LINE_NUMBER00(X)

static constexpr const std::uint32_t  RECORD_LINE_NUMBER(COORD_begin)
enum class COORD {
    ID_BASE = __LINE__- COORD_begin -2,
    X_MIN_T = __LINE__- COORD_begin -2,
    Y_MIN_T =__LINE__- COORD_begin -2,
    X_MAX_T = __LINE__- COORD_begin -2,
    Y_MAX_T = __LINE__- COORD_begin -2,
    POINT_DENSITY_T = __LINE__- COORD_begin -2,
    POINT_DENSITY_EXPONENT_T = __LINE__- COORD_begin -2,
    ITERATIONS_BASE = __LINE__- COORD_begin -2
};
//WIDTH_T = __LINE__- COORD_begin -2,
//HEIGHT_T = __LINE__- COORD_begin -2,


static constexpr const std::uint32_t  RECORD_LINE_NUMBER(TUPL_begin)
enum class TUPL {
    ID_T = __LINE__- TUPL_begin -2,
    BEGIN_T = __LINE__- TUPL_begin -2,
    END_T =__LINE__- TUPL_begin -2,
    AREA_T = __LINE__- TUPL_begin -2
};
//using NS_LogisticMap::TUPL;
#undef RECORD_LINE_NUMBER
#undef RECORD_LINE_NUMBER00
}

    
    
    
    
#endif // LOGISTICMAPBOUNDARYPOSTONSETOFCHAOS_H_27B82C95YD3898441D9383F44EE6159A9F
