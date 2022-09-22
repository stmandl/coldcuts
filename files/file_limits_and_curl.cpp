//
// Created by stm on 9/22/22.
//

#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <sstream>
#include <iostream>


// This program opens files and makes curl requests until
// the curl requests fail with a message like "Couldn't resolve..."


int get_num_fds()
{
    std::stringstream ps;
    ps << "/proc/" << getpid() << "/fd/";
    DIR* dp{::opendir(ps.str().c_str())};
    int entries{0};
    errno = 0;
    while (::readdir(dp))
    {
        ++entries;
    }
    if (errno != 0)
    {
        std::cerr << "DEBUG_STM:: error when reading dir: " << errno << " : " << strerror(errno)
                  << " :: " << strerrorname_np(errno) << " :::: " << strerrordesc_np(errno)
                  << std::endl;
        abort();
    }
    ::closedir(dp);
    return entries;
}


int get_open_file_limit()
{
    struct rlimit d;
    getrlimit(RLIMIT_NOFILE,&d);
    return d.rlim_max;
}

void set_open_file_limit(int l)
{
    struct rlimit d;
    d.rlim_max = d;
    setrlimit(RLIMIT_NOFILE,&d);
}

#include <charconv>
int get_max_fd()
{
    std::stringstream ps;
    ps << "/proc/" << getpid() << "/fd/";
    DIR* dp{::opendir(ps.str().c_str())};
    int entries{0};
    errno = 0;
    dirent* de = nullptr;
    int max_value = 0;
    while ((de = ::readdir(dp)) != nullptr)
    {
        int result{};
        const std::string name(de->d_name);
        auto [ptr, ec] {std::from_chars(name.begin(), name.end(), result) };
        if (ec == std::errc())
        {
            ++entries;
            if (result > max_value)
                max_value = result;
        }

    }
    if (errno != 0)
    {
        std::cerr << "DEBUG_STM:: error when reading dir: " << errno << " : " << strerror(errno)
                  << " :: " << strerrorname_np(errno) << " :::: " << strerrordesc_np(errno)
                  << std::endl;
        abort();
    }
    ::closedir(dp);
    return max_value;
}

int main(void)
{
    CURL *curl;
    CURLcode res;

    set_open_file_limit(32);
    assert(get_open_file_limit() == 32);

    for (int iter = 0; iter < get_open_file_limit(); iter++)
    {
        curl = curl_easy_init();
        if(curl) {
            std::cout<<"Open files: " << get_num_fds() << "/" << get_open_file_limit() << std::endl;
            std::stringstream fstr;

            fstr << "/var/tmp/stm/tmp_files/file_" << iter;
            fopen(fstr.str().c_str(),"w");

            /* I hope they won't hate us */
            curl_easy_setopt(curl, CURLOPT_URL, "https://pypi.org");
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            /* send all data to nvirvana  */
            FILE * dn = fopen("/dev/null", "w");
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, dn);

            /* Perform the request, res will get the return code */
            res = curl_easy_perform(curl);

            /* Check for errors */
            if(res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));

            /* always cleanup */
            curl_easy_cleanup(curl);
            fclose(dn);
        }
    }
    return 0;
}
