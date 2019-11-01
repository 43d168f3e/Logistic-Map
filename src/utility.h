// utility.h

#if 0
datum.h
#include "utility.h"
#include "src/utility.h"
#include "../src/utility.h"
#endif


#if !defined(utility_H_2z7b82c953898441d9383Kf44ee6159a9f)
#define utility_H_2z7b82c953898441d9383Kf44ee6159a9f


#if 0

0 <=  col_x <= (g_default___screen_width   - 1) ) ;  x_min_mpf <= x_t <= x_max_mpf
0 <=  row_y <= (g_default___screen_height  - 1) ) ;  y_min_mpf <= y_t <= y_max_mpf


    x_t = x_min_mpf + ( ( x_max_mpf - x_min_mpf )  / (g_default___screen_width   - 1) ) * col_x ;
    y_t = y_min_mpf + ( ( y_max_mpf - y_min_mpf )  / (g_default___screen_height  - 1) ) * row_y ;


    width_t  = x_max_mpf - x_min_mpf;
    height_t = y_max_mpf - y_min_mpf;

    x_t = x_min_mpf + ( width_t   / (g_default___screen_width   - 1) ) * col_x ;
    y_t = y_min_mpf + ( height_t  / (g_default___screen_height  - 1) ) * row_y ;

    normalized_width_t  = width_t  / (g_default___screen_width  - 1);
    normalized_height_t = height_t / (g_default___screen_height - 1);

    x_t = x_min_mpf + normalized_width_t  * col_x ; col_t = (x_t - x_min_mpf)/normalized_width_t;
    y_t = y_min_mpf + normalized_height_t * row_y ; row_t = (y_t - y_min_mpf)/normalized_height_t;


    rate_t = y_min_mpf + normalized_height_t * row_y; // ==  y_min_mpf + (y_max_mpf - y_min_mpf) * ( row_y / (g_default___screen_height-1) )
#endif
#if 0
#endif


#include "global.h"
    using mpf_pair = std::pair<mpf_class,mpf_class>;
    using mpf_2_tuple = std::tuple<mpf_class,mpf_class>;
    using mpf_4_tuple = std::tuple<mpf_class,mpf_class,mpf_class,mpf_class>;
#include <QSize>
#include <QPoint>
#include <QFile>

#include <type_traits>
#include <iostream>
#include <sstream>

#include <cstring>
#include <string>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <cctype>
#include <locale>
#include <fstream>
#include <tuple>
//clang++ needs -ldl
#include <vector>

///////////////////////////////////////////////////////////////////////////////
template<typename Type = double, const Type& Min = -10.0, const Type& Max = 10.0>
class Bounded
{
public:
    Bounded() {}
    Bounded(Type const & rhs) : val_{rhs} {
        if(rhs > Max || rhs < Min)
            throw std::domain_error("Out Of Bounds");
    }
    Bounded(Type&& j)   : val_{std::move(j)}{}
    Bounded(Bounded const & rhs)  = default;
    Bounded(Bounded&& rhs) noexcept = default;
    Bounded& operator=(Bounded const & rhs) {
        if(rhs > Max || rhs < Min)
            throw std::domain_error("Out Of Bounds");
        val_ = rhs;
        return *this;
    }
#if 0
    SYNTAX:
    typedef Bounded<double, -10.0, 10.0> double_10;
    double_10 d(-4.2);
    cout << "d = " << d << "\n";
#endif
    operator Type () const  {
        return val_;
    }
    operator Type& () {
        return val_;
    }
    bool operator==(Bounded const &rhs) const {
        static constexpr std::uint64_t g_{ static_cast<std::uint64_t>(-1) };
        auto range  = g_default___max__relativeDensity_exponent - g_default___min__relativeDensity_exponent;
        auto us     = (val_ - g_default___min__relativeDensity_exponent) / range;
        auto them   = (rhs - g_default___min__relativeDensity_exponent) / range;
        return (static_cast<std::uint64_t>(g_ * us) == static_cast<std::uint64_t>(g_ * them));
    }

    bool operator==(Type const &rhs) const {
        static constexpr std::uint64_t g_{ static_cast<std::uint64_t>(-1) };
        auto range  = g_default___max__relativeDensity_exponent - g_default___min__relativeDensity_exponent;
        auto us     = (val_ - g_default___min__relativeDensity_exponent) / range;
        auto them   = (rhs - g_default___min__relativeDensity_exponent) / range;
        return (static_cast<std::uint64_t>(g_ * us) == static_cast<std::uint64_t>(g_ * them));
    }

private:
    Type val_;
};


///////////////////////////////////////////////////////////////////////////////
//using bounded = Bounded<double, g_default___min__relativeDensity_exponent, g_default___max__relativeDensity_exponent>;
using bounded = double;
///////////////////////////////////////////////////////////////////////////////

#define RECORD_LINE_NUMBER00(X) X=__LINE__;
#define RECORD_LINE_NUMBER(X) RECORD_LINE_NUMBER00(X)
///////////////////////////////////////////////////////////////////////////////
static constexpr const int  RECORD_LINE_NUMBER(g_begin)
static constexpr const char g_ID_KEY[] = R"("ID": )";
static constexpr const char g_x_min_KEY[] = R"("x_min": )";
static constexpr const char g_y_min_KEY[] = R"("y_min": )";
static constexpr const char g_x_max_KEY[] = R"("x_max": )";
static constexpr const char g_y_max_KEY[] = R"("y_max": )";
static constexpr const char g_point_density_KEY[] = R"("D": )"; //point_density_t -> str
static constexpr const char g_point_density_exponent_KEY[] = R"("n": )"; //point_density_exponent_t -> str//D^n
static constexpr const char g_width_KEY[] = R"("width": )"; // display widget screen width (pixels)
static constexpr const char g_height_KEY[] = R"("height": )"; // display widget screen height (pixels)
static constexpr const char g_num_iterationsBASE_KEY[] = R"("N_base": )";
static constexpr const int  RECORD_LINE_NUMBER(g_end)
static constexpr const int  g_number_KEYS=g_end-g_begin-1;


#undef RECORD_LINE_NUMBER
#undef RECORD_LINE_NUMBER00
///////////////////////////////////////////////////////////////////////////////
constexpr const char* g_Keys[g_number_KEYS] = {
    g_ID_KEY,
    g_x_min_KEY,g_y_min_KEY,
    g_x_max_KEY,g_y_max_KEY,
    g_point_density_KEY,
    g_point_density_exponent_KEY,
    g_width_KEY,
    g_height_KEY,
    g_num_iterationsBASE_KEY
};
//g_number_KEYS == sizeof(g_Keys)/sizeof(g_Keys[0]);
using strnKeys = std::array< std::string , g_number_KEYS>;
///////////////////////////////////////////////////////////////////////////////

static constexpr const char g_POI_KEY[]="P.O.I.";
static constexpr const char g_POI_KEY_Text[]="description";
static constexpr const char g_POI_KEY_X[]="x";
static constexpr const char g_POI_KEY_Y[]="y";
static constexpr const char g_Q[]="\"";
static constexpr const char G_POI_KEY[]="\"P.O.I.\":[{\"";
static constexpr const char G_POI_KEY_Text[]="{\"description\" : {";
static constexpr const char G_POI_KEY_X[]="\"x\":";
static constexpr const char G_POI_KEY_Y[]="\"y\":";


using rects_tup = std::tuple<
std::size_t, // ID
std::string, // X_MIN_T
std::string, // Y_MIN_T
std::string, // X_MAX_T
std::string, // Y_MAX_T
std::string, // POINT_DENSITY_T
std::string, // POINT_DENSITY_EXPONENT_T
std::uint32_t, // WIDTH_T
std::uint32_t, // HEIGHT_T
std::uint32_t  // ITERATIONS_BASE
>;


using rect_tup = std::tuple<
std::size_t, // ID
mpf_class, // X_MIN_T
mpf_class, // Y_MIN_T
mpf_class, // X_MAX_T
mpf_class, // Y_MAX_T
mpf_class, // POINT_DENSITY_T
mpf_class, // POINT_DENSITY_EXPONENT_T
std::uint32_t, // WIDTH_T
std::uint32_t, // HEIGHT_T
std::uint32_t  // ITERATIONS_BASE
>;


using RECT_TUP_Ptr    = std::shared_ptr< rect_tup >;
using RECTS_TUP_Ptr   = std::shared_ptr< rects_tup >;
class LogisticMap_data_structure;
using LogisticMap_Data_Structure_Ptr   = std::shared_ptr< LogisticMap_data_structure >;
///////////////////////////////////////////////////////////////////////////////
    using MPF_Ptr	   = std::shared_ptr< mpf_class const >;
    using MPF_Vec	   = std::vector<  MPF_Ptr  >;
    using MPF_Vec_Ptr  = std::shared_ptr< MPF_Vec >;
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
template< class charT >
bool isZero( charT ch, const std::locale& loc ) {
    auto Z = static_cast<charT>( 48 /*"0"*/);
    //return std::use_facet<std::ctype<charT>>(loc).is("0", ch);
    return /*std::use_facet<std::ctype<charT>>(loc).is(std::ctype_base::digit, ch)
           &&*/ Z == ch;
}
static inline void r0trim(std::string &s) {
//    if (s == "0.0" || s == "0." || s == "0" || s == ".0") return;
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !isZero<decltype(ch)>(ch, std::locale(""));
    }).base(), s.end());
}
static inline std::string r0trim_copy(std::string s) {
    r0trim(s);
//    int a = s[s.length()]; == 0
//    int a1 = s[s.length()-1];
//    int b = *s.end(); == 0
//    int b1 = *(--s.end());
//    int b1a = *(s.end()-1);
    if (static_cast<char>( 46 /*"."*/) == *(s.end()-1) ) s += "0";
    return s;
}

static bool my_isspace(char ch)
{
    return std::isspace(static_cast<unsigned char>(ch));
}

static inline std::string remove_ws(std::string in) {
      in.erase(std::remove_if(in.begin(), in.end(), my_isspace), in.end());
      return in;
    }

///////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string as_string(T const& x , bool wrap = false) {
    using value_type = std::remove_cv_t<std::remove_reference_t<T>>;
    if constexpr((std::is_same_v<value_type, mpf_class&>)||(std::is_same_v<value_type, mpf_class>)) {
        mpf_set_default_prec (NS_LogisticMap::prec);
        std::ostringstream oss;
        oss.precision(NS_LogisticMap::prec+2);
        oss  << std::fixed << x ;//<< std::ends;
//ERRORS: oss  << std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec+2) << x ;//<< std::ends;
        //std::ostream&      oss_ref = oss;
//auto prev = oss_ref.rdbuf (std::cout.rdbuf ());
        std::string s0= oss.str();
        std::string s1 = remove_ws(s0);
        std::string s2 = r0trim_copy(s0);
        std::string s3 = r0trim_copy(s1);
        std::string s4  = "\"" + s3 + "\"";
        if (wrap) return s4;
        return s3;
    }
    else if constexpr(std::is_arithmetic_v<value_type>) {
        return std::to_string(x);
    }
    else if constexpr(std::is_same_v<T, std::string>) {
        return x;//std::move(x);//x;
    }
    else if constexpr((std::is_same_v<value_type, bounded&>)||(std::is_same_v<value_type, bounded>)) {
        return std::to_string(x);
    }
    else return std::string(x);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//x^y
static mpf_class pow(mpf_class const & x, double const & _y)
{//x^y
	mpf_class ret;
    mpf_class y = _y;
	mpfr_t tmpx, tmpy;
	mpfr_init2(tmpx, mpf_get_default_prec());
	mpfr_init2(tmpy, mpf_get_default_prec());
	mpfr_set_f(tmpx, x.get_mpf_t(), GMP_RNDN);
	mpfr_set_f(tmpy, y.get_mpf_t(), GMP_RNDN);
	mpfr_pow(tmpx, tmpx, tmpy, GMP_RNDN);
	mpfr_get_f(ret.get_mpf_t(), tmpx, GMP_RNDN);

	return ret;
}
///////////////////////////////////////////////////////////////////////////////
/// \brief pow
/// \param x
/// \param y
/// \return
///
static mpf_class pow(const mpf_class& x, const mpf_class& y)
{//x^y
	mpf_class ret;
	mpfr_t tmpx, tmpy;
	mpfr_init2(tmpx, mpf_get_default_prec());
	mpfr_init2(tmpy, mpf_get_default_prec());
	mpfr_set_f(tmpx, x.get_mpf_t(), GMP_RNDN);
	mpfr_set_f(tmpy, y.get_mpf_t(), GMP_RNDN);
	mpfr_pow(tmpx, tmpx, tmpy, GMP_RNDN);
	mpfr_get_f(ret.get_mpf_t(), tmpx, GMP_RNDN);

	return ret;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#if 0
static void wait_for_key ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    std::cout << std::endl << "Press ENTER to continue..." << std::endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
    int inputNumerator, inputDenominator;
    char slash;
    if ((std::cin >> inputNumerator >> slash >> inputDenominator) && slash == '/')
    {
      /* ... */
    }
    else
    {
        std::cin.clear(); // reset the fail flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore the bad input until line end
        throw std::invalid_argument("Invalid syntax.");
    }
}
#endif


#endif // utility_H_2z7b82c953898441d9383Kf44ee6159a9f
