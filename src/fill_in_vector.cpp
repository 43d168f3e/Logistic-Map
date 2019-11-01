#include "fill_in_vector.h"

//std::mutex Fill_in_vector::worker_mutex;

vec_mem_tup_ibeA_t Fill_in_vector::g_vec_mem_tup_ibeA_t;
vec_idANDbeginANDendANDarea Fill_in_vector::vibeA;
std::size_t Fill_in_vector::m_selected{0} ;
mpf_class Fill_in_vector::x_min_mpf ;//= dotstr.x_min_mpf;
mpf_class Fill_in_vector::y_min_mpf ;//= dotstr.y_min_mpf;
mpf_class Fill_in_vector::x_max_mpf ;//= dotstr.x_max_mpf;
mpf_class Fill_in_vector::y_max_mpf ;//= dotstr.y_max_mpf;
mpf_class Fill_in_vector::height_t ;//= dotstr.height_t;
mpf_class Fill_in_vector::width_t ;//= dotstr.width_t;
mpf_class Fill_in_vector::normalized_height_t ;//= dotstr.normalized_height_t;
mpf_class Fill_in_vector::normalized_width_t ;//= dotstr.normalized_width_t;
QRgb Fill_in_vector::num_iterations_base{1000};
double Fill_in_vector::increase_sample_size_by{1} ;


std::atomic<std::uint32_t> Fill_in_vector::num_THREADS{static_cast<std::uint32_t>(-1)};

std::atomic<bool> Fill_in_vector::m_abort{false};
std::atomic<std::uint32_t> Fill_in_vector::whose_turn{static_cast<std::uint32_t>(-1)};

