#include <unistd.h>

static int	ft_nbr(int n)
{
	char	c;
	int	count;

	if (n == -2147483648)
	{
		write (1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		count++;
	}
	if (n >= 10)
		count += ft_nbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
	count++;
	return(count);
}

int	ft_print_nbr(int n)
{
	return (ft_nbr(n));
}