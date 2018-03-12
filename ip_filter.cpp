//g++ ip_filter.cpp -o ip_filter --std=c++14
//./ip_filter < ip.tsv > out.tsv

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using ipPool = std::vector<std::vector<int> >;

std::vector<int> ip_parse(auto & v)
{
    auto ip = std::vector<int> {};
    std::for_each(v.begin(), v.end(), [& ip](auto s){ip.emplace_back(std::stoi(s));});
    return ip;
}

void print_ip(auto ip)
{
    for(auto ip_part = ip.begin(); ip_part != ip.end(); ++ip_part)
        {
            if(ip_part != ip.begin())
                std::cout << '.';
            std::cout << *ip_part;
        }
    std::cout << std::endl;
}

void output(auto ip_pool)
{
    std::for_each(ip_pool.begin(), ip_pool.end(), [](auto ip){print_ip(ip);} );
}

template<int N = 0>
void ip_copy_if (auto & ip_pool, auto & v){
	std::copy(ip_pool.begin(), ip_pool.end(), back_inserter(v));
}

template<int N = 0, typename T, typename... Args>
void ip_copy_if(auto & ip_pool, auto & v, T t, Args... args){

    ipPool buff;
    std::copy_if(ip_pool.begin(), ip_pool.end(),
				std::back_inserter(buff),
				[t](auto x){
					return (x[N] == t);
				}
	);
	ip_copy_if<N+1>(buff, v, std::forward<Args>(args)...);
}

void ip_copy_if_any(auto & ip_pool, auto & v, int f)
{
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(v), [f](auto x){return std::any_of(x.begin(), x.end(), [f](auto i){return i == f;});});
}

int main(int argc, char const *argv[])
{
    try
    {
        ipPool ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            if (line.length() == 0) continue;
            auto v = std::vector<std::string> {};
            boost::split(v, line, boost::is_any_of("\t "));
            boost::split(v, v.at(0), boost::is_any_of("."));
            ip_pool.emplace_back(ip_parse(v));
        }

        std::sort(ip_pool.begin(), ip_pool.end(), [](auto a, auto b){return std::make_tuple(a) > std::make_tuple(b); });
        output(ip_pool);

        ipPool v2;
        ip_copy_if(ip_pool, v2, 1);
        ip_copy_if(ip_pool, v2, 46, 70);
        ip_copy_if_any(ip_pool, v2, 46);
        output(v2);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

