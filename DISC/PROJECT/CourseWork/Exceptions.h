#pragma once
#include <string>

namespace exc
{
	class ExceptionBase
	{
	public:
		ExceptionBase(std::string problem)
		{
			_problem = problem;
		}
		const std::string & What()
		{
			return _problem;
		}

	private:
		std::string _problem;
	};

	class InvalidGameObjectParameters
		:public ExceptionBase
	{
	public:
		InvalidGameObjectParameters(std::string problem_defenition) :ExceptionBase(problem_defenition)
		{
		}
	};

}