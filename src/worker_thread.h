//worker_thread.h
#if 0
worker_thread.h
#include "worker_thread.h"
#include "src/worker_thread.h"
#include "../src/worker_thread.h"
#endif


#if !defined(worker_thread_H_df675692345dfsdfg3412a04939b7d4047814fb59d2)
#define worker_thread_H_df675692345dfsdfg3412a04939b7d4047814fb59d2

#include "fill_in_vector.h"
#include <mutex>
#include <condition_variable>
#include <QDebug>
#include <QImage>

#if 0
#endif

///////////////////////////////////////////////////////////////////////////////

namespace WORKER_THREAD
{
std::mutex               files_lock;
std::condition_variable  status_changed;
    bool initialize(std::size_t const selected, std::uint32_t const num_THREADS)
    {
        std::lock_guard<std::mutex> lk(files_lock);
        try {
            Datum const& dum = Data::datum(selected);
            assert(dum.ID_v() == selected);

            Fill_in_vector::m_selected = selected;
            Fill_in_vector::m_abort = false;
            Fill_in_vector::whose_turn = static_cast<std::uint32_t>(-1);
            Fill_in_vector::num_THREADS  = num_THREADS;

        Fill_in_vector::x_min_mpf    = dum.x_min_v();
        Fill_in_vector::y_min_mpf    = dum.y_min_v();
        Fill_in_vector::x_max_mpf    = dum.x_max_v();
        Fill_in_vector::y_max_mpf    = dum.y_max_v();
        Fill_in_vector::width_t    = dum.width_v(); //width_t  = x_max_mpf - x_min_mpf;
        Fill_in_vector::height_t   = dum.height_v();//height_t = y_max_mpf - y_min_mpf;
        Fill_in_vector::normalized_width_t = dum.normalized_width_v(); //= width_t  / (mpf_class{g_default___screen_width  - 1});
        Fill_in_vector::normalized_height_t = dum.normalized_height_v();//= height_t / (mpf_class{g_default___screen_height - 1});

        Fill_in_vector::num_iterations_base    = dum.num_iterationsBASE_v();
        Fill_in_vector::increase_sample_size_by = dum.get_increase_sample_size_by();

        std::uint32_t quotient  = g_default___screen_height / num_THREADS;
        std::uint32_t modulo	= g_default___screen_height % num_THREADS;
        assert  (g_default___screen_height == quotient * num_THREADS + modulo);
        Q_ASSERT(g_default___screen_height == quotient * num_THREADS + modulo);

        Fill_in_vector::vibeA.clear();
        //for (auto &e : Fill_in_vector::g_vec_mem_tup_ibeA_t ) e.first = nullptr;
        Fill_in_vector::g_vec_mem_tup_ibeA_t.clear();
        calculate_area_begin_end_id( Fill_in_vector::vibeA,  num_THREADS);//, g_default___screen_width , g_default___screen_height);

        } catch(const std::exception& e) {
            std::cout << e.what() << '\n';
            return false;
        }
        return true;
    }

}
///////////////////////////////////////////////////////////////////////////////
#endif // worker_thread_H_df675692345dfsdfg3412a04939b7d4047814fb59d2
