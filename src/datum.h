// datum.h

#if 0
datum.h
#include "datum.h"
#include "src/datum.h"
#include "../src/datum.h"
#endif


#if !defined(DATUM_H_2z7b82c953898441d9383Kf44ee6159a9f)
#define DATUM_H_2z7b82c953898441d9383Kf44ee6159a9f


#include "utility.h"

#if 0

0 <=  col_x <= (g_default___g_default___screen_width   - 1) ) ;  x_min_mpf <= x_t <= x_max_mpf
0 <=  row_y <= (g_default___g_default___screen_height  - 1) ) ;  y_min_mpf <= y_t <= y_max_mpf


x_t = x_min_mpf + ( ( x_max_mpf - x_min_mpf )  / (g_default___g_default___screen_width   - 1) ) * col_x ;
y_t = y_min_mpf + ( ( y_max_mpf - y_min_mpf )  / (g_default___g_default___screen_height  - 1) ) * row_y ;


width_t  = x_max_mpf - x_min_mpf;
height_t = y_max_mpf - y_min_mpf;

x_t = x_min_mpf + ( width_t   / (g_default___g_default___screen_width   - 1) ) * col_x ;
y_t = y_min_mpf + ( height_t  / (g_default___g_default___screen_height  - 1) ) * row_y ;

normalized_width_t  = width_t  / (g_default___g_default___screen_width  - 1);
normalized_height_t = height_t / (g_default___g_default___screen_height - 1);

x_t = x_min_mpf + normalized_width_t  * col_x ; col_t = (x_t - x_min_mpf)/normalized_width_t;
y_t = y_min_mpf + normalized_height_t * row_y ; row_t = (y_t - y_min_mpf)/normalized_height_t;


rate_t = y_min_mpf + normalized_height_t * row_y; // ==  y_min_mpf + (y_max_mpf - y_min_mpf) * ( row_y / (g_default___g_default___screen_height-1) )
#endif
#if 0
#endif
///////////////////////////////////////////////////////////////////////////////
class LMap;
//using bounded = Bounded<double, g_default___min__relativeDensity_exponent, g_default___max__relativeDensity_exponent>;
using bounded = double;
///////////////////////////////////////////////////////////////////////////////
/// \brief The Datum class
///
class Datum
{
    friend LMap;
private:
    nlohmann::json jsn;
//data:
    std::size_t m_ID{static_cast<std::size_t>(-1)};

    mpf_class m_x_min_mpf{g_default___x_min_mpf};
    mpf_class m_y_min_mpf{g_default___y_min_mpf};
    mpf_class m_x_max_mpf{g_default___x_max_mpf};
    mpf_class m_y_max_mpf{g_default___y_max_mpf};
    mpf_class m_point_density_mpf{g_default___point_density_mpf};

    bounded m_point_density_exponent_d{g_default___point_density_exponent_d};
    std::uint32_t m_num_iterationsBASE_i{g_default___num_iterationsBASE_i};

public:
    nlohmann::json const& get_json(void) const {return jsn;}
    Datum();// : jsn{} {}
//~Datum(){}
///////////////////////////////////////////////////////////////////////////////
    static Datum datum_cache_parameter_changes;//{};
///////////////////////////////////////////////////////////////////////////////
/// \brief Datum
/// \param id
/// \param x_min_s
/// \param y_min_s
/// \param x_max_s
/// \param y_max_s
/// \param point_density_s
/// \param _point_density_exponent
/// \param _num_iterationsBASE
///  for: construction from HISTORY file
    Datum(std::size_t id,
          std::string const& x_min_s,
          std::string const& y_min_s,
          std::string const& x_max_s,
          std::string const& y_max_s,
          std::string const& point_density_s,
          double  const& _point_density_exponent,
          std::uint32_t _num_iterationsBASE,
          bool b_update_datum_cache_parameter_changes = false) :
        m_ID{id},
        m_point_density_exponent_d{_point_density_exponent},
        m_num_iterationsBASE_i{_num_iterationsBASE}
    {

        write_json_using_numerical();
    //check:
        m_point_density_exponent_d = point_density_exponent();
        assert(m_point_density_exponent_d == _point_density_exponent);
        m_num_iterationsBASE_i = num_iterationsBASE();
        assert(m_num_iterationsBASE_i == _num_iterationsBASE);

        initialize();
        if (b_update_datum_cache_parameter_changes) cache();
    //record_history();
    }
///////////////////////////////////////////////////////////////////////////////
    Datum(std::size_t id,
          mpf_class const& x_min,
          mpf_class const& y_min,
          mpf_class const& x_max,
          mpf_class const& y_max,
          mpf_class const& point_density,
          double  const& _point_density_exponent,
          std::uint32_t  _num_iterationsBASE,
          bool b_update_datum_cache_parameter_changes = false)  noexcept  :
        m_ID{id},
        m_x_min_mpf{x_min},
        m_y_min_mpf{y_min},
        m_x_max_mpf{x_max},
        m_y_max_mpf{y_max},
        m_point_density_mpf{ point_density },
        m_point_density_exponent_d{_point_density_exponent},
        m_num_iterationsBASE_i{_num_iterationsBASE}

    {
        calculate_width_and_height_using_numerical();
        write_json_using_numerical();
        if (b_update_datum_cache_parameter_changes) cache();
    //record_history();
    }
///////////////////////////////////////////////////////////////////////////////
    Datum(std::size_t id,
          mpf_class&& x_min,
          mpf_class&& y_min,
          mpf_class&& x_max,
          mpf_class&& y_max,
          mpf_class const& point_density,
          double  const& _point_density_exponent,
          std::uint32_t  _num_iterationsBASE,
          bool b_update_datum_cache_parameter_changes = false)  noexcept  :
        m_ID{id},
        m_x_min_mpf{std::move(x_min)},
        m_y_min_mpf{std::move(y_min)},
        m_x_max_mpf{std::move(x_max)},
        m_y_max_mpf{std::move(y_max)},
        m_point_density_mpf{ point_density },
        m_point_density_exponent_d{_point_density_exponent},
        m_num_iterationsBASE_i{_num_iterationsBASE}

    {
        calculate_width_and_height_using_numerical();
        write_json_using_numerical();
        if (b_update_datum_cache_parameter_changes) cache();
    //record_history();
    }
///////////////////////////////////////////////////////////////////////////////
    Datum(Datum const &d,
          bool b_update_datum_cache_parameter_changes = false) :
        m_ID{d.m_ID},
        m_x_min_mpf{d.m_x_min_mpf},
        m_y_min_mpf{d.m_y_min_mpf},
        m_x_max_mpf{d.m_x_max_mpf},
        m_y_max_mpf{d.m_y_max_mpf},
        m_point_density_mpf{ d.m_point_density_mpf },
        m_point_density_exponent_d{ d.m_point_density_exponent_d },
        m_num_iterationsBASE_i{ d.m_num_iterationsBASE_i }
    {
        calculate_width_and_height_using_numerical();
        write_json_using_numerical();
        if (b_update_datum_cache_parameter_changes) cache();
    //record_history();
    }
///////////////////////////////////////////////////////////////////////////////
    Datum(Datum &&d,
          bool b_update_datum_cache_parameter_changes = false)  noexcept :
        m_ID{std::move(d.m_ID)},
        m_x_min_mpf{std::move(d.m_x_min_mpf)},
        m_y_min_mpf{std::move(d.m_y_min_mpf)},
        m_x_max_mpf{std::move(d.m_x_max_mpf)},
        m_y_max_mpf{std::move(d.m_y_max_mpf)},
        m_point_density_mpf{std::move(d.m_point_density_mpf) },
        m_point_density_exponent_d{std::move(d.m_point_density_exponent_d) },
        m_num_iterationsBASE_i{std::move(d.m_num_iterationsBASE_i) }
    {
        calculate_width_and_height_using_numerical();
        write_json_using_numerical();
        if (b_update_datum_cache_parameter_changes) cache();
    //record_history();
    }
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//auto operator=(const Datum& rhs) &          -> Datum& = default;
///////////////////////////////////////////////////////////////////////////////
//auto operator=(Datum&& rhs)      & noexcept -> Datum& = default;
///////////////////////////////////////////////////////////////////////////////
    Datum& operator=(Datum  const & d/*,
                     bool b_update_datum_cache_parameter_changes = false*/){
        m_ID = d.m_ID;
        m_x_min_mpf = d.m_x_min_mpf;
        m_y_min_mpf = d.m_y_min_mpf;
        m_x_max_mpf = d.m_x_max_mpf;
        m_y_max_mpf = d.m_y_max_mpf;
        m_point_density_mpf =  d.m_point_density_mpf ;
        m_point_density_exponent_d =  d.m_point_density_exponent_d ;
        m_num_iterationsBASE_i =  d.m_num_iterationsBASE_i;
        calculate_width_and_height_using_numerical();
        write_json_using_numerical();
        //if (b_update_datum_cache_parameter_changes) cache();
        return *this;
    }
///////////////////////////////////////////////////////////////////////////////
    Datum&  operator=(Datum&& d/*,
                      bool b_update_datum_cache_parameter_changes = false*/) noexcept {
        this->m_ID = std::move(d.m_ID);
        this->m_x_min_mpf = std::move(d.m_x_min_mpf);
        this->m_y_min_mpf = std::move(d.m_y_min_mpf);
        this->m_x_max_mpf = std::move(d.m_x_max_mpf);
        this->m_y_max_mpf = std::move(d.m_y_max_mpf);
        this->m_point_density_mpf = std::move(d.m_point_density_mpf) ;
        this->m_point_density_exponent_d = std::move(d.m_point_density_exponent_d) ;
        this->m_num_iterationsBASE_i = std::move(d.m_num_iterationsBASE_i) ;
        calculate_width_and_height_using_numerical();
        write_json_using_numerical();
        //if (b_update_datum_cache_parameter_changes) cache();
        return *this;
    }
///////////////////////////////////////////////////////////////////////////////
    void calculate_width_and_height_using_numerical(void)
    {
        m_width_mpf  = m_x_max_mpf - m_x_min_mpf;
        m_height_mpf = m_y_max_mpf - m_y_min_mpf;

    //x_t = x_min_mpf + ( ( x_max_mpf - x_min_mpf )  / (g_default___g_default___screen_width   - 1) ) * col_x  = x_min_mpf + ( width_t   / (g_default___g_default___screen_width   - 1) ) * col_x
    //        = x_min_mpf + m_normalized_width_mpf * col_x ;
    //y_t = y_min_mpf + ( ( y_max_mpf - y_min_mpf )  / (g_default___g_default___screen_height  - 1) ) * row_y  = y_min_mpf + ( height_t  / (g_default___g_default___screen_height  - 1) ) * row_y
    //        = y_min_mpf + m_normalized_height_mpf * row_y ;

        m_normalized_width_mpf  = m_width_mpf  / (mpf_class{g_default___screen_width  - 1});
        m_normalized_height_mpf = m_height_mpf / (mpf_class{g_default___screen_height - 1});
    }
///////////////////////////////////////////////////////////////////////////////
    void record_history(void) const;
///////////////////////////////////////////////////////////////////////////////
    void cache(void)  {
        Datum::datum_cache_parameter_changes.x_min_ref() = m_x_min_mpf;
        Datum::datum_cache_parameter_changes.y_min_ref() = m_y_min_mpf;
        Datum::datum_cache_parameter_changes.x_max_ref() = m_x_max_mpf;
        Datum::datum_cache_parameter_changes.y_max_ref() = m_y_max_mpf;
        Datum::datum_cache_parameter_changes.calculate_width_and_height_using_numerical();

        Datum::datum_cache_parameter_changes.point_density_ref() = m_point_density_mpf;
        Datum::datum_cache_parameter_changes.point_density_exponent_ref() = m_point_density_exponent_d;
        Datum::datum_cache_parameter_changes.num_iterationsBASE_ref() = m_num_iterationsBASE_i;
        Datum::datum_cache_parameter_changes.write_json_using_numerical();
    }
///////////////////////////////////////////////////////////////////////////////
    void write_JSON(std::string const & fileName)   /*bugged??*/ const ;
///////////////////////////////////////////////////////////////////////////////
    void write_json_using_numerical(void)
    {
        jsn["ID_BASE"] = as_string<decltype(m_ID)>(m_ID);
        jsn["X_MIN_T"] = as_string<decltype(m_x_min_mpf)>(m_x_min_mpf);
        jsn["Y_MIN_T"] = as_string<decltype(m_y_min_mpf)>(m_y_min_mpf);
        jsn["X_MAX_T"] = as_string<decltype(m_x_max_mpf)>(m_x_max_mpf);
        jsn["Y_MAX_T"] = as_string<decltype(m_y_max_mpf)>(m_y_max_mpf);
        jsn["POINT_DENSITY_T"] = as_string<decltype(m_x_min_mpf)>(m_point_density_mpf);
        jsn["POINT_DENSITY_EXPONENT_T"] = as_string<decltype(m_point_density_exponent_d)>(m_point_density_exponent_d);
        jsn["ITERATIONS_BASE"] = as_string<decltype(m_num_iterationsBASE_i)>(m_num_iterationsBASE_i);
    }
///////////////////////////////////////////////////////////////////////////////
    void initialize(void) {
        m_ID = ID();

        m_x_min_mpf = x_min();
        m_y_min_mpf = y_min();
        m_x_max_mpf = x_max();
        m_y_max_mpf = y_max();
        m_point_density_mpf = point_density();
        m_point_density_exponent_d = point_density_exponent();
        m_num_iterationsBASE_i = num_iterationsBASE();

        calculate_width_and_height_using_numerical();
    }
///////////////////////////////////////////////////////////////////////////////
// information:
    std::size_t ID(void) const {return static_cast<std::size_t>( std::stoi(jsn["ID_BASE"].get<std::string>()) );}

    mpf_class x_min(void) const {return mpf_class{jsn["X_MIN_T"].get<std::string>().c_str(), NS_LogisticMap::prec, 10};}
    mpf_class y_min(void) const {return mpf_class{jsn["Y_MIN_T"].get<std::string>().c_str(), NS_LogisticMap::prec, 10};}
    mpf_class x_max(void) const {return mpf_class{jsn["X_MAX_T"].get<std::string>().c_str(), NS_LogisticMap::prec, 10};}
    mpf_class y_max(void) const {return mpf_class{jsn["Y_MAX_T"].get<std::string>().c_str(), NS_LogisticMap::prec, 10};}
    mpf_class point_density(void) const {return mpf_class{jsn["POINT_DENSITY_T"].get<std::string>().c_str(), NS_LogisticMap::prec, 10};}

    double point_density_exponent(void) const {return std::stod(jsn["POINT_DENSITY_EXPONENT_T"].get<std::string>());}
    std::uint32_t num_iterationsBASE(void) const {return static_cast<std::uint32_t>( std::stoi(jsn["ITERATIONS_BASE"].get<std::string>()) );}



    mpf_class width (void) const {return x_max() - x_min();}
    mpf_class height(void) const {return y_max() - y_min();}
    mpf_class normalized_width (void) const {return  width() / (mpf_class{g_default___screen_width  - 1});}
    mpf_class normalized_height(void) const {return height() / (mpf_class{g_default___screen_height - 1});}


//
    std::string ID_s(void) const    {return jsn["ID_BASE"].get<std::string>();}
    std::string x_min_s(void) const {return jsn["X_MIN_T"].get<std::string>();}
    std::string y_min_s(void) const {return jsn["Y_MIN_T"].get<std::string>();}
    std::string x_max_s(void) const {return jsn["X_MAX_T"].get<std::string>();}
    std::string y_max_s(void) const {return jsn["Y_MAX_T"].get<std::string>();}
    std::string point_density_s(void) const {return jsn["POINT_DENSITY_T"].get<std::string>();}
    std::string point_density_exponent_s(void) const {return  jsn["POINT_DENSITY_EXPONENT_T"].get<std::string>();}
    std::string num_iterationsBASE_s(void) const {return jsn["ITERATIONS_BASE"].get<std::string>();}
///////////////////////////////////////////////////////////////////////////////
// aux data:
    mpf_class m_width_mpf; //width_t  = x_max_mpf - x_min_mpf;
    mpf_class m_height_mpf;//height_t = y_max_mpf - y_min_mpf;

//x_t = x_min_mpf + ( width_t   / (g_default___g_default___screen_width   - 1) ) * col_x ;
//y_t = y_min_mpf + ( height_t  / (g_default___g_default___screen_height  - 1) ) * row_y ;

    mpf_class m_normalized_width_mpf; //= width_t  / (mpf_class{g_default___g_default___screen_width  - 1});
    mpf_class m_normalized_height_mpf;//= height_t / (mpf_class{g_default___g_default___screen_height - 1});
///////////////////////////////////////////////////////////////////////////////
// query info:
    std::size_t  ID_v(void) const {return m_ID;}
    mpf_class  const &x_min_v(void) const {return m_x_min_mpf;}
    mpf_class  const &y_min_v(void) const {return m_y_min_mpf;}
    mpf_class  const &x_max_v(void) const {return m_x_max_mpf;}
    mpf_class  const &y_max_v(void) const {return m_y_max_mpf;}
    mpf_class  const &point_density_v(void) const {return m_point_density_mpf;}

    bounded const & point_density_exponent_v(void) const {return m_point_density_exponent_d;}
    std::uint32_t num_iterationsBASE_v(void) const {return m_num_iterationsBASE_i;}

    mpf_class  const &width_v (void) const {return m_width_mpf ;}
    mpf_class  const &height_v(void) const {return m_height_mpf;}
    mpf_class  const &normalized_width_v (void) const {return m_normalized_width_mpf ;}
    mpf_class  const &normalized_height_v(void) const {return m_normalized_height_mpf;}
///////////////////////////////////////////////////////////////////////////////
// assignment:
    mpf_class &x_min_ref(void)   {return m_x_min_mpf;}
    mpf_class &y_min_ref(void)   {return m_y_min_mpf;}
    mpf_class &x_max_ref(void)   {return m_x_max_mpf;}
    mpf_class &y_max_ref(void)   {return m_y_max_mpf;}
    mpf_class &point_density_ref(void)   {return m_point_density_mpf;}

    double &point_density_exponent_ref(void)   {return m_point_density_exponent_d;}
    std::uint32_t &num_iterationsBASE_ref(void)   {return m_num_iterationsBASE_i;}

    mpf_class &normalized_width_ref (void)  {return m_normalized_width_mpf ;}
    mpf_class &normalized_height_ref(void)  {return m_normalized_height_mpf;}


///////////////////////////////////////////////////////////////////////////////
/// \brief get_mpf_XY_tuple
/// \param pos
/// \return
///

    mpf_2_tuple get_mpf_XY_tuple( /*mpf_class const &x_min_mpf, mpf_class const &y_min_mpf,
                                                  mpf_class const &normalized_width_t, mpf_class const &normalized_height_t,*/
                                  QPoint const &pos) const {
        mpf_set_default_prec (NS_LogisticMap::prec);
    //	mpf_class width_t  = x_max_mpf - x_min_mpf;
    //	mpf_class height_t = y_max_mpf - y_min_mpf;
    //	mpf_class normalized_width_t  = width_t  / (g_default___g_default___screen_width  - 1);
    //	mpf_class normalized_height_t = height_t / (g_default___g_default___screen_height - 1);

    //          ************  WARNING  ************
    // drops to double precision ACCURACY [for some reason]
    // if one uses  ... normalized_width_t  * pos.x()
        mpf_class x_t = m_x_min_mpf + m_normalized_width_mpf  * mpf_class{pos.x()} ;// col_t = (x_t - x_min_mpf)/normalized_width_t;
        mpf_class y_t = m_y_min_mpf + m_normalized_height_mpf * mpf_class{pos.y()} ;// row_t = (y_t - y_min_mpf)/normalized_height_t;
        return {x_t, y_t};
    //mpf_class y_t = y_min_mpf + normalized_height_t *((g_default___g_default___screen_height - 1) - pos.y() );// row_t = (y_t - y_min_mpf)/normalized_height_t;
    }
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
    mpf_class get_rectangleArea(void) const {
        mpf_class rectangleArea_t = m_width_mpf * m_height_mpf;
        return rectangleArea_t;
    }
///////////////////////////////////////////////////////////////////////////////
    std::uint32_t get_screen_Row_y( mpf_class const &y_t ) const {
        mpf_class row_t = ( y_t - y_min_v() ) / normalized_height_v() ;// row_t = (y_t - y_min_mpf)/normalized_height_t;
        std::uint32_t row_y = static_cast<QRgb >(mpf_get_ui(row_t.get_mpf_t()));
        return row_y;
    }
///////////////////////////////////////////////////////////////////////////////
    std::uint32_t get_screen_Col_x( mpf_class const &x_t ) const {
        mpf_class col_t = ( x_t - x_min_v() ) / normalized_width_v() ;
        std::uint32_t col_x = static_cast<std::uint32_t>( mpf_get_ui(col_t.get_mpf_t()));
        return col_x;
    }
//QRgb get_screen_Row_y(mpf_class const &rate_t) const {
//return Data::vec_LogisticMap_Data::get_screen_Row_y(rate_t);}
///////////////////////////////////////////////////////////////////////////////
    mpf_class get_x_mpf( QRgb col_x) const {
        mpf_set_default_prec (NS_LogisticMap::prec);
        mpf_class x = x_min_v() + normalized_width_v() * col_x ;
        return x;
    }
///////////////////////////////////////////////////////////////////////////////
    mpf_class get_y_mpf( QRgb row_y) const {
        mpf_set_default_prec (NS_LogisticMap::prec);
        mpf_class y = y_min_v() + normalized_height_v() * row_y ;// row_t = (y_t - y_min_mpf)/normalized_height_t;
        return y;// == R
    }
///////////////////////////////////////////////////////////////////////////////
    double get_increase_sample_size_by(void) const {
        mpf_class point_density_exponent = (double)point_density_exponent_v();
        mpf_class D_n =  pow( point_density_v(), point_density_exponent );

    //mpf_class D_n =  pow(m_point_density_mpf, m_point_density_exponent_d);
    //mpf_class D_n =  pow( point_density_v(), point_density_exponent_v());
        double d_n = mpf_get_d( D_n.get_mpf_t() );
        return d_n;
    }
///////////////////////////////////////////////////////////////////////////////
    QRgb get_num_iterations(void) const {
        return static_cast<QRgb>(
                    num_iterationsBASE_v() * get_increase_sample_size_by()
                    );
    }
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
};
//    std::uint32_t g_default___g_default___screen_width{g_default___g_default___screen_width};
//    std::uint32_t g_default___g_default___screen_height{g_default___g_default___screen_height};
//    mpf_class x_min_mpf(x_min_s.c_str(), NS_LogisticMap::prec, 10);
//    std::uint32_t g_default___g_default___screen_width{g_default___g_default___screen_width};
//    std::uint32_t g_default___g_default___screen_height{g_default___g_default___screen_height};

//    // strings
//        std::string s1 = "Hello, world!";
//        json js = s1;
//        auto s2 = js.get<std::string>();

//    // Booleans
//        bool b1 = true;
//        json jb = b1;
//        auto b2 = jb.get<bool>();

//    // numbers
//        int i = 42;
//        json jn = i;
//        auto f = jn.get<double>();

#endif // DATUM_H_2z7b82c953898441d9383Kf44ee6159a9f
