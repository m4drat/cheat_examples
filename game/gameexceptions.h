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