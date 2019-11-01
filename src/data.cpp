#include "data.h"

std::vector< Datum > Data::vec_LogisticMap_Data;
Data::Data()
{

}

///////////////////////////////////////////////////////////////////////////////
/// \brief gotoThisRate
/// \param newRate_s
/// \param fixedAspectRatio
/// \param aspectRatio
/// \return
///
std::size_t Data::gotoThisRate(std::string const &newRate_s, bool fixedAspectRatio) {
    if ( vec_LogisticMap_Data.empty() ) return static_cast<std::size_t>(-1);
    mpf_class center_x;
    mpf_class dX;
    mpf_class dY;
    mpf_class dy;
    Datum dum{};
        assert(dum.ID_v() == static_cast<std::size_t>(-1));
    mpf_class rectangleAreaBASE = dum.get_rectangleArea();

    auto a31 = newRate_s.empty();
    auto a32 = newRate_s.length();
    auto a33 = newRate_s.size();
    auto a34 = newRate_s.c_str();
    auto a35 = sizeof(a34);
    auto a36 = strlen(a34);// != sizeof(a34) because of byte padding

    char copy[1024];
    //if (strlcpy(copy, a34, a36) >= a36) return -1;
    std::strncpy((char*)copy, (const char *)a34, a36);
    /* add a final null terminator */
    copy[a36] = 0;
    auto a37 = sizeof(copy);
    auto a38 = strlen((char*)copy);

    if (a31) {
        return static_cast<std::size_t>(-1);
    }
    if (a35==0||a35==1) {
        return static_cast<std::size_t>(-1);
    }
    mpf_class rate_t{(const char *)copy, NS_LogisticMap::prec, 10};

//    mpf_class rate_t(newRate_s.c_str(), NS_LogisticMap::prec, 10);

    if (dum.y_max_v() >= rate_t && rate_t >= dum.y_min_v()) {
        dY = dum.y_max_v() - rate_t;
        dy = rate_t - dum.y_min_v();
        if (dY > dy) {
            dum.y_max_ref() = rate_t + dy;
        }
        else if (dY < dy) {
            dum.y_min_ref() = rate_t - dY;
        }
        if (fixedAspectRatio) {
            dX = g_default___aspectRatio*(dum.y_max_v() - dum.y_min_v())/2;
            center_x = (dum.x_max_v() + dum.x_min_v())/2;
            dum.x_max_ref() = center_x + dX;
            dum.x_min_ref() = center_x - dX;
        }
        dum.calculate_width_and_height_using_numerical();
        //dum.initialize();
        //++dum.m_ID;

        mpf_class rectangleArea_new = ( dum.x_max_v() - dum.x_min_v() ) * ( dum.y_max_v() - dum.y_min_v() );
        //mpf_class rectangleArea_t = dum.get_rectangleArea();
        mpf_class point_density =  ( dum.point_density_v() * rectangleAreaBASE ) / rectangleArea_new;
        dum.point_density_ref() = point_density;

        return Data::add_datum(
                    std::move(dum.x_min_ref()),
                    std::move(dum.y_min_ref()),
                    std::move(dum.x_max_ref()),
                    std::move(dum.y_max_ref()),
                    dum.point_density_v(),
                    dum.point_density_exponent_v(),
                    dum.num_iterationsBASE_v() );
//        vec_LogisticMap_Data.emplace_back( std::make_shared< Data::vec_LogisticMap_Data >(dum) );

//        UpdateInterface(dum.m_ID);
//        return vec_LogisticMap_Data.size()-1;
        //return std::make_shared< Data::vec_LogisticMap_Data >(dum);
    }
#if 0
    dY = g_y_max_t - rate_t;
    dy = rate_t - g_y_min_t;
    if (dY > dy) {
        dum.y_max_ref() = rate_t + dy;
    }
    else if (dY < dy) {
        dum.y_min_ref() = rate_t - dY;
    }
    if (fixedAspectRatio) {
        mpf_class dX = aspectRatio*(dum.y_max_v() - dum.y_min_v())/2;
        mpf_class center_x = (dum.x_max_v() + dum.x_min_v())/2;
        dum.x_max_ref() = center_x + dX;
        dum.x_min_ref() = center_x - dX;
    }
        dum.initialize();
        ++dum.m_ID;
        mpf_class rectangleArea_t = dum.get_rectangleArea();
        dum.point_density_ref() = ( point_density_mpf * rectangleAreaBASE_t ) / rectangleArea_t;
        vec_LogisticMap_Data.emplace_back( std::make_shared< Data::vec_LogisticMap_Data >(dum) );

//        UpdateInterface(dum.m_ID);
        return vec_LogisticMap_Data.size()-1;
        //return std::make_shared< Data::vec_LogisticMap_Data >(dum);
#endif
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
mpf_4_tuple Data::get_mpf_Xmin_Ymin_Xmax_Ymax_4_tuple( std::size_t index, QPoint const &screenPT_1, QPoint const &screenPT_2 ) {
    QPoint p=screenPT_1;
    if (auto outsideregion = {
            p.rx() < static_cast<int>(g_default___screen_col_min),
            p.rx() > static_cast<int>(g_default___screen_col_max),
            p.ry() < static_cast<int>(g_default___screen_row_min),
            p.ry() > static_cast<int>(g_default___screen_row_max)
};
           std::any_of(outsideregion.begin(), outsideregion.end(),
                       [](const bool& kw) { return true == kw; })) {
        throw std::invalid_argument("point 1 on boundary.");
       }
    p=screenPT_2;
    if (auto outsideregion = {
            p.rx() < static_cast<int>(g_default___screen_col_min),
            p.rx() > static_cast<int>(g_default___screen_col_max),
            p.ry() < static_cast<int>(g_default___screen_row_min),
            p.ry() > static_cast<int>(g_default___screen_row_max)
};
           std::any_of(outsideregion.begin(), outsideregion.end(),
                       [](const bool& kw) { return true == kw; })) {
        throw std::invalid_argument("point 2 on boundary.");
       }

    mpf_set_default_prec (NS_LogisticMap::prec);
    mpf_class _x_min_t , _x_max_t , _y_min_t , _y_max_t;

    try {
        Datum const& dum = Data::datum(index);
        assert(dum.ID_v() == index);
//auto [_x_min_t , _y_min_t] = dum.get_mpf_XY_tuple( screenPT_1 );
//auto [_x_max_t , _y_max_t] = dum.get_mpf_XY_tuple( screenPT_2 );
mpf_2_tuple a1 = dum.get_mpf_XY_tuple( screenPT_1 );
mpf_2_tuple a2 = dum.get_mpf_XY_tuple( screenPT_2 );

_x_min_t=std::move(std::get<0>(a1));
_y_min_t=std::move(std::get<1>(a1));
_x_max_t=std::move(std::get<0>(a2));
_y_max_t=std::move(std::get<1>(a2));
}
catch (const std::out_of_range& oor) {
  std::cout << "LMap::play_rubberBand_Rect() Out of Range error: " << oor.what() << '\n';
  return {g_default___x_min_mpf,g_default___x_max_mpf,g_default___y_min_mpf,g_default___y_max_mpf};
}
catch (std::invalid_argument const& iaex) {
    std::cout << "LMap::ComputeMap: abort " << iaex.what()  << std::endl;
    return {g_default___x_min_mpf,g_default___x_max_mpf,g_default___y_min_mpf,g_default___y_max_mpf};
}
catch(const std::exception& e) {
    std::cout << "LMap::play_rubberBand_Rect() " << e.what() << '\n';
    return {g_default___x_min_mpf,g_default___x_max_mpf,g_default___y_min_mpf,g_default___y_max_mpf};
}
catch (...) {
    std::cerr << "LMap::play_rubberBand_Rect() \n";
    return {g_default___x_min_mpf,g_default___x_max_mpf,g_default___y_min_mpf,g_default___y_max_mpf};
}
//std::get<0>(a1),//std::move(_x_min_t),
//std::get<1>(a1),//std::move(_y_min_t),
//std::get<0>(a2),//std::move(_x_max_t),
//std::get<1>(a2),//std::move(_y_max_t),

if (_x_min_t > _x_max_t)	{
    mpf_class max = _x_min_t;
    _x_min_t = _x_max_t;
    _x_max_t = max;
}
if (_y_min_t > _y_max_t)	{
    mpf_class max = _y_min_t;
    _y_min_t = _y_max_t;
    _y_max_t = max;
}


if ( _x_min_t < g_default___x_min_mpf ) _x_min_t = g_default___x_min_mpf ;
if ( _y_min_t < g_default___y_min_mpf ) _y_min_t = g_default___y_min_mpf ;
if ( _x_max_t > g_default___x_max_mpf)  _x_max_t = g_default___x_max_mpf ;
if ( _y_max_t > g_default___y_max_mpf)  _y_max_t = g_default___y_max_mpf ;

return {_x_min_t , _y_min_t , _x_max_t , _y_max_t};
}
///////////////////////////////////////////////////////////////////////////////
std::size_t Data::newRegion( std::size_t index, QPoint const &screenPT_1,  QPoint const &screenPT_2) {
        if ( vec_LogisticMap_Data.empty() ) return static_cast<std::size_t>(-1);
//mpf_class _x_min_t , _x_max_t , _y_min_t , _y_max_t;

        mpf_set_default_prec (NS_LogisticMap::prec);
        try {
            Datum const& dum = Data::datum(index);
            assert(dum.ID_v() == index);
            auto [_x_min_t , _y_min_t, _x_max_t , _y_max_t] = get_mpf_Xmin_Ymin_Xmax_Ymax_4_tuple( index, screenPT_1, screenPT_2 );
#if 0
        QPoint P1{screenPT_1};
        QPoint P2{screenPT_2};
        QPoint center = (P1+P2)/2;
        const double widthScreen  = g_default___screen_width;
        const double heightScreen = g_default___screen_height;
        const int iwidthScreen  = static_cast<int>(g_default___screen_width);
        const int iheightScreen = static_cast<int>(g_default___screen_height);
    //ERRORS: auto result = std::minmax_element(&x[0], &x[ncols-1]);
    //-O0 (do no optimization, the default if no optimization level is specified)
    //-O == -O1 (optimize minimally) -Og (Optimize debugging experience.
        std::pair<int, int> result_x = std::minmax(P1.x(), P2.x());// FAIL: /*auto*/ unless  -Og
        std::pair<int, int> result_y = std::minmax(P1.y(), P2.y());
        int x_min = result_x.first;//P1.x();
        int y_min = result_y.first;//P1.y();
        int x_max = result_x.second;//P2.x();
        int y_max = result_y.second;//P2.y();
        if (x_min == x_max) {
            return static_cast<std::size_t>(-1);// nullptr;
        }
        if (y_min == y_max) {
            return static_cast<std::size_t>(-1);// nullptr;//exit(-2);//return std::make_shared< MPF_Vec > (nullptr);
        }

        if (x_max < 0)	return static_cast<std::size_t>(-1);//nullptr;
        if (x_min >= iwidthScreen)	return static_cast<std::size_t>(-1);// nullptr;
        if (y_max < 0)	return static_cast<std::size_t>(-1);// nullptr;
        if (y_min >= iheightScreen)	return static_cast<std::size_t>(-1);// nullptr;

        if (x_min < 0)	x_min = 0;
        if (x_max >= iwidthScreen)	x_max = iwidthScreen-1;
        if (y_min < 0)	y_min = 0;
        if (y_max >= iheightScreen)	y_max = iheightScreen-1;

        double w = static_cast<double>( x_max - x_min );
        double h = static_cast<double>( y_max - y_min );
        P1.setX(center.x() - static_cast<int>( w/2 ) );//lower left
        P1.setY(center.y() - static_cast<int>( h/2 ) );
        P2.setX(center.x() + static_cast<int>( w/2 ) );//top right
        P2.setY(center.y() + static_cast<int>( h/2 ) );

        auto [_x_min_t , _y_min_t] = dum.get_mpf_XY_tuple( P1 );
        auto [_x_max_t , _y_max_t] = dum.get_mpf_XY_tuple( P2 );
                mpf_2_tuple a1 = dum.get_mpf_XY_tuple( P1 );
                mpf_2_tuple a2 = dum.get_mpf_XY_tuple( P2 );

            if (_x_min_t > _x_max_t)	{
                mpf_class max = _x_min_t;
                _x_min_t = _x_max_t;
                _x_max_t = max;
            }
            if (_y_min_t > _y_max_t)	{
                mpf_class max = _y_min_t;
                _y_min_t = _y_max_t;
                _y_max_t = max;
            }
#endif


mpf_class rectangleArea_new = ( _x_max_t - _x_min_t ) * ( _y_max_t - _y_min_t );
mpf_class rectangleAreaBASE = dum.get_rectangleArea();
mpf_class point_density =  ( dum.point_density_v() * rectangleAreaBASE ) / rectangleArea_new;

    return Data::add_datum(
                std::move(_x_min_t),
                std::move(_y_min_t),
                std::move(_x_max_t),
                std::move(_y_max_t),
                point_density,
                Datum::datum_cache_parameter_changes.point_density_exponent_v(),
                Datum::datum_cache_parameter_changes.num_iterationsBASE_v()
                );
//                std::get<0>(a1),//std::move(_x_min_t),
//                std::get<1>(a1),//std::move(_y_min_t),
//                std::get<0>(a2),//std::move(_x_max_t),
//                std::get<1>(a2),//std::move(_y_max_t),
//                _x_min_t,
//                _y_min_t,
//                _x_max_t,
//                _y_max_t,
//                dum.point_density_v(),
//                dum.point_density_exponent_v(),
//                dum.num_iterationsBASE_v() );
//            newJ.x_min_mpf = _x_min_t;
//            newJ.y_min_mpf = _y_min_t;
//            newJ.x_max_mpf = _x_max_t;
//            newJ.y_max_mpf = _y_max_t;
//            newJ.initialize();
//            ++newJ.m_ID;


//            mpf_class rectangleArea_t = newJ.get_rectangleArea();
//            newJ.point_density_mpf = ( point_density_mpf * rectangleAreaBASE_t ) / rectangleArea_t;

//            vec_LogisticMap_Data.emplace_back( std::make_shared< vec_LogisticMap_Data >(newJ) );
//            UpdateInterface(newJ.m_ID);
            //return vec_LogisticMap_Data.size()-1;
        } catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
    }
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
