#ifndef _CLOUD_BUS_THREAD_LOCK_H_
#define _CLOUD_BUS_THREAD_LOCK_H_


#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
#ifndef WIN32_LEAN_AND_MEAN
#define  WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#elif defined(__VXWORKS__)
#include <types/vxWind.h>
#include <semLib.h>
#elif defined(__QNXNTO__) || (HERMES_OS == HERMES_OS_LINUX)
#include <pthread.h>

#endif


class thread_lock
{
public:
    thread_lock()
    {
#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
        InitializeCriticalSection(&m_cs);
#elif defined(__VXWORKS__)
        m_semId = semMCreate();
#elif defined(__QNXNTO__) || (HERMES_OS == HERMES_OS_LINUX)
        pthread_mutex_init(&m_mutex, NULL);
#endif
    }
    ~thread_lock()
    {
#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
        DeleteCriticalSection(&m_cs);
#elif defined(__VXWORKS__)
        semDelete(m_semId);
#elif defined(__QNXNTO__) || (HERMES_OS == HERMES_OS_LINUX)
        pthread_mutex_destroy(&m_mutex);
#endif
    }

    void lock()
    {
#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
        EnterCriticalSection(&m_cs);
#elif defined(__VXWORKS__)
        semTake(m_semId, WAIT_FOREVER );
#elif defined(__QNXNTO__) || (HERMES_OS == HERMES_OS_LINUX)
        pthread_mutex_lock(&m_mutex);
#endif
    }

    void unlock()
    {
#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
        LeaveCriticalSection(&m_cs);
#elif defined(__VXWORKS__)
        semGive(m_semId);
#elif defined(__QNXNTO__) || (HERMES_OS == HERMES_OS_LINUX)
        pthread_mutex_unlock(&m_mutex);
#endif
    }

private:
#if (HERMES_OS == HERMES_OS_WINDOWS_NT)
    CRITICAL_SECTION    m_cs;
#elif defined(__VXWORKS__)
    SIM_ID				m_semId;
#elif defined(__QNXNTO__) || (HERMES_OS == HERMES_OS_LINUX)
    pthread_mutex_t 	m_mutex;
#endif
};


#endif
