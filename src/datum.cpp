
#include "utility.h"
#include "datum.h"

Datum Datum::datum_cache_parameter_changes{};

Datum::Datum()
{
    m_ID = static_cast<std::size_t>(-1);
    jsn["ID_BASE"] = as_string<decltype(m_ID)>(m_ID);
    jsn["X_MIN_T"] = as_string<decltype(m_x_min_mpf)>(m_x_min_mpf);
    jsn["Y_MIN_T"] = as_string<decltype(m_x_min_mpf)>(m_y_min_mpf);
    jsn["X_MAX_T"] = as_string<decltype(m_x_min_mpf)>(m_x_max_mpf);
    jsn["Y_MAX_T"] = as_string<decltype(m_x_min_mpf)>(m_y_max_mpf);
    jsn["POINT_DENSITY_T"] = as_string<decltype(m_x_min_mpf)>(m_point_density_mpf);
    jsn["POINT_DENSITY_EXPONENT_T"] = as_string<decltype(m_point_density_exponent_d)>(m_point_density_exponent_d);
    jsn["ITERATIONS_BASE"] = as_string<decltype(m_num_iterationsBASE_i)>(m_num_iterationsBASE_i);


    m_width_mpf  = m_x_max_mpf - m_x_min_mpf;
    m_height_mpf = m_y_max_mpf - m_y_min_mpf;

    //x_t = x_min_mpf + ( ( x_max_mpf - x_min_mpf )  / (g_default___screen_width   - 1) ) * col_x  = x_min_mpf + ( width_t   / (g_default___screen_width   - 1) ) * col_x
    //        = x_min_mpf + m_normalized_width_mpf * col_x ;
    //y_t = y_min_mpf + ( ( y_max_mpf - y_min_mpf )  / (g_default___screen_height  - 1) ) * row_y  = y_min_mpf + ( height_t  / (g_default___screen_height  - 1) ) * row_y
    //        = y_min_mpf + m_normalized_height_mpf * row_y ;

    m_normalized_width_mpf  = m_width_mpf  / (mpf_class{g_default___screen_width  - 1});
    m_normalized_height_mpf = m_height_mpf / (mpf_class{g_default___screen_height - 1});

}
///////////////////////////////////////////////////////////////////////////////
void Datum::record_history() const {
}
///////////////////////////////////////////////////////////////////////////////
void Datum::write_JSON(std::string const & fileName)   /*bugged??*/ const  {
    QFile file(fileName.c_str());
    bool ok = file.open(QIODevice::ReadWrite | QIODevice::Text);
    if (!ok) {
        std::cout << fileName << " -File creation and/or opening failed\n";
        return;
    }
    file.close();
    std::fstream outf(fileName);
if(!outf) {  // operator! is used here
    std::cout << fileName << " -File opening failed\n";
    return;
}
std::stringstream out;
//out << "{\n\"" << str_nKeys[0] << "\":{";
out << "{";

out << g_ID_KEY << m_ID << ","  << std::endl;

out << g_x_min_KEY << as_string<decltype(m_x_min_mpf)>(m_x_min_mpf, true) << ","  << std::endl;
out << g_y_min_KEY << as_string<decltype(m_y_min_mpf)>(m_y_min_mpf, true) << ","  << std::endl;
out << g_x_max_KEY << as_string<decltype(m_x_max_mpf)>(m_x_max_mpf, true) << ","  << std::endl;
out << g_y_max_KEY << as_string<decltype(m_y_max_mpf)>(m_y_max_mpf, true) << ","  << std::endl;
out << g_point_density_KEY << as_string<decltype(m_point_density_mpf)>(m_point_density_mpf, true)  << "," << std::endl;

out << g_point_density_exponent_KEY << m_point_density_exponent_d << ","  << std::endl;

out << g_width_KEY << g_default___screen_width << ","  << std::endl;
out << g_height_KEY << g_default___screen_height << ","  << std::endl;
out << g_num_iterationsBASE_KEY << m_num_iterationsBASE_i << std::endl;

out << "}";

std::size_t I=0;
int c = outf.peek();
if (c == EOF) {
    outf.clear();
    outf.put('[');
    outf << out.str();
    outf.put(']');
    outf /*<< std::ends*/ << std::flush;
    outf.close();
    std::cout << "c == EOF:outf.close();END@@ CPU::addItem(MPF_Vec_Ptr const &newBoundaryPtr, int setw)" << std::endl;
    //return m_selected;
}
else {
    I=0;
    outf.seekg(std::ios_base::end);
    while (outf.peek() != ']') {
        I++;
        outf.seekg(-I, std::ios_base::end);
    }
    c = outf.peek();
    if (c == ']') {
    outf.put(',');
    outf.put('\n');
    outf << out.str();
    outf.put(']');
    outf /*<< std::ends*/ << std::flush;
    outf.close();
    }
    else {
    std::cout << "ERROR: closing curley brace '}' NOT found\nCPU::addItem(MPF_Vec_Ptr const &newBoundaryPtr, int setw)" << std::endl;
    }
}
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#if 0
void Datum::write_JSON(std::string const & fileName) const  {
    QFile file(fileName.c_str());
    bool ok = file.open(QIODevice::ReadWrite | QIODevice::Text);
    if (!ok) {
        std::cout << fileName << " -File creation and/or opening failed\n";
        return;
    }
    //QString qs = file.readAll();    //QByteArray ba = file.readAll();
    file.close();
    std::fstream outf(fileName);
    //std::fstream outf(fileName, outf.trunc | outf.out);//the openmodes ios_base::in and ios_base::out are specified by default. This means that std::fstream f("test.txt", std::ios_base::in | std::ios_base::out); is the same as std::fstream f("test.txt");
if(!outf) {  // operator! is used here
    std::cout << fileName << " -File opening failed\n";
    return;
}
#if 0
///////////////////////////////////////////////////////////////////////////////
/// \brief gets_data
/// \return
///
    RECTS_TUP_Ptr gets_data(void) {
        rects_tup  data = std::make_tuple(
        m_ID,
        x_min_s,y_min_s,x_max_s,y_max_s,point_density_s,point_density_exponent_s,
        screen_width,screen_height,num_iterationsBASE
        );
    return std::make_shared< rects_tup >(data);
}
///////////////////////////////////////////////////////////////////////////////
static_cast<unsigned long>()

    str8_t getStr_newBoundaryPtr(MPF_Vec_Ptr const &newBoundPtr); -> gets_data
    void set_JSON_data_structure_Boundary( MPF_Vec_Ptr const &newBoundPtr );
    MPF_Vec_Ptr get_JSON_data_structure_Boundary(void) const;
#endif

//auto daeta = std::make_tuple(
//        m_ID,
//        x_min_s,y_min_s,x_max_s,y_max_s,point_density_s,point_density_exponent_s,
//        g_default___screen_width,g_default___screen_height,num_iterationsBASE
//        );

//auto data = *gets_data().get();
strnKeys str_nKeys;
std::size_t I=0;
//for_each_in_tuple(data, [&str_nKeys,&I](const auto &x) { str_nKeys[I] = as_string<decltype(x)>( x );  ++I;});
//for (const auto& e: str_nKeys) {
//    std::cout << e << std::endl;
//}

std::stringstream out;
//out << "{\n\"" << str_nKeys[0] << "\":{";
out << "{";


out << g_ID_KEY << m_ID << std::endl;
out << g_x_min_KEY << as_string<decltype(m_x_min_mpf)>(m_x_min_mpf, true) << std::endl;
out << g_y_min_KEY << as_string<decltype(m_y_min_mpf)>(m_y_min_mpf, true) << std::endl;
out << g_x_max_KEY << as_string<decltype(m_x_max_mpf)>(m_x_max_mpf, true) << std::endl;
out << g_y_max_KEY << as_string<decltype(m_y_max_mpf)>(m_y_max_mpf, true) << std::endl;
out << g_point_density_KEY << as_string<decltype(m_point_density_mpf)>(m_point_density_mpf, true) << std::endl;
out << g_point_density_exponent_KEY << g_Keys[I] << std::endl;
out << g_width_KEY << g_Keys[I] << std::endl;
out << g_height_KEY << g_Keys[I] << std::endl;
out << g_num_iterationsBASE_KEY << g_Keys[I] << std::endl;

out << "}";

I=0;
for (const auto& e: str_nKeys) {
    std::cout << std::string(4, ' ') << e << std::string(4, '\t') << g_Keys[I] << std::endl;
    if (I != g_number_KEYS-1) {
    out << "\"" << g_Keys[I] << "\":" << e << "," << std::endl;
    }
    else {
    out << "\"" << g_Keys[I] << "\":" << e <<  std::endl;
    }
    I++;
}
//out << "}\n}";
out << "}";


int c = outf.peek();
if (c == EOF) {
    outf.clear();
    outf.put('[');
    outf << out.str();
    outf.put(']');
    outf /*<< std::ends*/ << std::flush;
    outf.close();
    std::cout << "c == EOF:outf.close();END@@ CPU::addItem(MPF_Vec_Ptr const &newBoundaryPtr, int setw)" << std::endl;
    //return m_selected;
}
else {
    I=0;
    outf.seekg(std::ios_base::end);
    while (outf.peek() != ']') {
        I++;
        outf.seekg(-I, std::ios_base::end);
    }
    c = outf.peek();
    if (c == ']') {
    outf.put(',');
    outf.put('\n');
    outf << out.str();
    outf.put(']');
    outf /*<< std::ends*/ << std::flush;
    outf.close();
    }
    else {
    std::cout << "ERROR: closing curley brace '}' NOT found\nCPU::addItem(MPF_Vec_Ptr const &newBoundaryPtr, int setw)" << std::endl;
    }
}
}

#endif
