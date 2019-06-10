#pragma once

struct NegativeHealException : public std::exception
{
	const char *what() const throw ()
	{
		return "Negative heal exception\n";
	}
};

struct NegativeDamageException : public std::exception
{
	const char *what() const throw ()
	{
		return "Negative damage exception\n";
	}
};

struct NegativeGoldException : public std::exception
{
	const char *what() const throw ()
	{
		return "Negative gold exception\n";
	}
};

struct NegativeExpException : public std::exception
{
	const char *what() const throw ()
	{
		return "Negative experience exception\n";
	}
};
