// data.h

#if 0
datum.h
#include "data.h"
#include "src/data.h"
#include "../src/data.h"
#endif


#if !defined(DATA_H_2z7b82c9A5389834J441d9383Kf44ee6159a9f)
#define DATA_H_2z7b82c9A5389834J441d9383Kf44ee6159a9f


#include "datum.h"

///////////////////////////////////////////////////////////////////////////////
class Data
{
public:
    static std::vector< Datum > vec_LogisticMap_Data;
///////////////////////////////////////////////////////////////////////////////
    static Datum const& datum(std::size_t index)  {
        //return index < vec_LogisticMap_Data.size()? vec_LogisticMap_Data[index] : throw std::out_of_range("index " + std::to_string(index) + " is out of range");
        auto size = vec_LogisticMap_Data.size();
        if ( index >= size ) throw std::out_of_range("index " + std::to_string(index) + " is out of range");
        return vec_LogisticMap_Data[index];
    }
///////////////////////////////////////////////////////////////////////////////
    Data();
///////////////////////////////////////////////////////////////////////////////
    static std::size_t add_datum(
                          std::string const& x_min_s,
                          std::string const& y_min_s,
                          std::string const& x_max_s,
                          std::string const& y_max_s,
                          std::string const& point_density_s,
                          double  const& point_density_exponent,
                          std::uint32_t num_iterationsBASE)
    {
        std::size_t ret = vec_LogisticMap_Data.size();
        vec_LogisticMap_Data.emplace_back(
                    /*Datum{*/  ret,
                               x_min_s,
                               y_min_s,
                               x_max_s,
                               y_max_s,
                               point_density_s,
                               point_density_exponent,
                               num_iterationsBASE, true /*}*/
                    );
        return ret;
    }
///////////////////////////////////////////////////////////////////////////////
    static std::size_t add_datum(
           mpf_class&& x_min,
           mpf_class&& y_min,
           mpf_class&& x_max,
           mpf_class&& y_max,
           mpf_class const& point_density,
           double  const& point_density_exponent,
           std::uint32_t num_iterationsBASE)
    {
        std::size_t ret = vec_LogisticMap_Data.size();
        vec_LogisticMap_Data.emplace_back(
                    /*Datum{*/  ret,
                    std::move(x_min),
                    std::move(y_min),
                    std::move(x_max),
                    std::move(y_max),
//                               x_min,
//                               y_min,
//                               x_max,
//                               y_max,
                               point_density,
                               point_density_exponent,
                               num_iterationsBASE, true/*}*/
                    );
        return ret;
    }
///////////////////////////////////////////////////////////////////////////////
    static std::size_t add_datum(Datum const &d)
    {
        std::size_t ret = vec_LogisticMap_Data.size();
        vec_LogisticMap_Data.emplace_back(d, true);
        return ret;
    }
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
    static std::size_t gotoThisRate(std::string const &newRate_s, bool fixedAspectRatio);
///////////////////////////////////////////////////////////////////////////////
    static mpf_4_tuple get_mpf_Xmin_Ymin_Xmax_Ymax_4_tuple(  std::size_t index, QPoint const &screenPT_1, QPoint const &screenPT_2 );
    static std::size_t  newRegion( std::size_t index, QPoint const &pos1,  QPoint const &pos2);
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
    static std::size_t translate_mpf_XY(  std::size_t index_parent, QPoint const &screen_point) {
        if ( vec_LogisticMap_Data.empty() ) return static_cast<std::size_t>(-1);
        mpf_set_default_prec (NS_LogisticMap::prec);
        try {
            Datum const& dum = Data::datum(index_parent);
            assert(dum.ID_v() == index_parent);

        //mpf_class rectangleAreaBASE_t = dum.get_rectangleArea();
        mpf_class x0_t = (dum.x_min_v()+ dum.x_max_v())/2;
        mpf_class y0_t = (dum.y_min_v()+ dum.y_max_v())/2;
        mpf_class x_t = dum.x_min_v() + dum.normalized_width_v()  * mpf_class{screen_point.x()} ;// col_t = (x_t - x_min_mpf)/normalized_width_t;
        mpf_class y_t = dum.y_min_v() + dum.normalized_height_v() * mpf_class{screen_point.y()} ;// row_t = (y_t - y_min_mpf)/normalized_height_t;
        mpf_class delta_x_t = x_t - x0_t;
        mpf_class delta_y_t = y_t - y0_t;
        mpf_class new_x_min_mpf = dum.x_min_v() + delta_x_t;
        mpf_class new_x_max_mpf = dum.x_max_v() + delta_x_t;
        mpf_class new_y_min_mpf = dum.y_min_v() + delta_y_t;
        mpf_class new_y_max_mpf = dum.y_max_v() + delta_y_t;


        return Data::add_datum(
                    std::move(new_x_min_mpf),
                    std::move(new_y_min_mpf),
                    std::move(new_x_max_mpf),
                    std::move(new_y_max_mpf),
                    dum.point_density_v(),
                    dum.point_density_exponent_v(),
                    dum.num_iterationsBASE_v()
                    );
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
    }

};

#endif // DATA_H_2z7b82c9A5389834J441d9383Kf44ee6159a9f
