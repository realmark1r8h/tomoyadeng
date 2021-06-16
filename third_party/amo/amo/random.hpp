#ifndef AMO_RANDOM_HPP
#define AMO_RANDOM_HPP
 
#include <limits>
// - random                   : building
#ifdef BOOST_NO_CXX11_HDR_RANDOM
#include <amo/config.hpp>
#else
#include <random>
#endif

// uniform_smallint����С�������ڵľ��ȷֲ�  
// uniform_int�����������ϵľ��ȷֲ�  
// uniform_01��������[0,1]�ϵ�ʵ���������ȷֲ�  
// uniform_real��������[min,max]�ϵ�ʵ���������ȷֲ�  
// bernoulli_distribution����Ŭ���ֲ�  
// binomial_distribution������ֲ�  
// cauchy_distribution�������������ȣ��ֲ�  
// gamma_distribution��٤��ֲ�  
// poisson_distribution�����ɷֲ�  
// geometric_distribution�����ηֲ�  
// triangle_distribution�����Ƿֲ�  
// exponential_distribution��ָ���ֲ�  
// normal_distribution����̬�ֲ�  
// lognormal_distribution��������̬�ֲ�  
// uniform_on_sphere��������ȷֲ�  

 
namespace amo
{
#ifdef BOOST_NO_CXX11_HDR_RANDOM
	using boost::random::random_device;
	using boost::random::uniform_int_distribution;
	using boost::random::uniform_real_distribution;
	using boost::random::normal_distribution;
#else
	using std::random_device;
	using std::uniform_int_distribution;
	using std::uniform_real_distribution;
	using std::normal_distribution;

#endif
	 
	 
	template<typename T = uniform_int_distribution<int> >
	class random
	{
	public:
		random(typename T::result_type min = 0, typename T::result_type max = (std::numeric_limits<typename T::result_type>::max)())
			: m_min(min)
			, m_max(max)
			, gen(min, max)
		{

		}

		typename T::result_type operator()()
		{
			return gen(rng);
		}
	private:
		random_device rng;
		T gen;
		typename T::result_type m_min;
		typename T::result_type m_max;
	};

	template<>
	class random < int >
	{
	public:
		random(int min = 0, int max = (std::numeric_limits<int>::max)())
			: m_min(min)
			, m_max(max)
			, gen(min, max)
		{

		}

		int operator()()
		{
			return gen(rng);
		}

	private:
		random_device rng;
		uniform_int_distribution<> gen;
		int m_min;
		int m_max;
	};

	template<>
	class random<double>
	{
	public:
		random(double min = 0, double max = (std::numeric_limits<double>::max)())
			: m_min(min)
			, m_max(max)
			, gen(min, max)
		{

		}

		double operator()()
		{
			return gen(rng);
		}

	private:
		random_device rng;
		uniform_real_distribution<> gen;
		double m_min;
		double m_max;
	};


	template<>
	class random < float >
	{
	public:
		random(float min = 0, float max = (std::numeric_limits<float>::max)())
			: m_min(min)
			, m_max(max)
			, gen(min, max)
		{

		}

		float operator()()
		{
			return static_cast<float>(gen(rng));
		}

	private:
		random_device rng;
		uniform_real_distribution<> gen;
		float m_min;
		float m_max;
	};
}
#endif // AMO_RANDOM_DEVICE_HPP
