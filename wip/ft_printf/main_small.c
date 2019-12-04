#include <stdio.h>
#include "ft_printf.h"

int main(int argc, char **argv)
{
	int r1;
	int r2;

	r1 = printf("%03*.*o", 3, -15, 0);
	fflush(stdout);
	write(1, "\n", 1);
	r2 = ft_printf("%03*.*o", 3, -15, 0);
	write(1, "\n", 1);
	if (r1 != r2)
		printf("return err: %d != %d\n", r1, r2);

	r1 = printf("%03*.o", 3, 0);
	fflush(stdout);
	write(1, "\n", 1);
	r2 = ft_printf("%03*.o", 3, 0);
	write(1, "\n", 1);
	if (r1 != r2)
		printf("return err: %d != %d\n", r1, r2);

//	r1 = printf("%-54lc", (char)176);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("%-54lc", (char)176);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);

//	r1 = printf("__%03*d__", -15, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*d__", -15, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.*d__", 3, -15, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.*d__", 3, -15, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.3d__", 0, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.3d__", 0, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.10d__", 3, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.10d__", 3, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%3d__", 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%3d__", 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%.3d__", 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%.3d__", 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%*.3d__", 10, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%*.3d__", 10, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.3d__", 10, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.3d__", 10, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.d__", 10, 123);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.d__", 10, 123);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.c__", 3, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.c__", 3, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.3c__", 3, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.3c__", 3, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.s__", 3, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.s__", 3, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.3s__", 10, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.3s__", 10, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.*x__", 3, -15, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.*x__", 3, -15, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.x__", 3, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.x__", 3, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.3x__", 10, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.3x__", 10, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.*p__", 10, -15, 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.*p__", 10, -15, 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%p__", 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%p__", 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%.0p__", 0);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%.0p__", 0);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.%__", 3);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.%__", 3);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);
//
//	r1 = printf("__%03*.*Z__", 3, -15, 123);
//	fflush(stdout);
//	write(1, "\n", 1);
//	r2 = ft_printf("__%03*.*Z__", 3, -15, 123);
//	write(1, "\n", 1);
//	if (r1 != r2)
//		printf("return err: %d != %d\n", r1, r2);

//	r1 = printf("%0*.3d\n", 10, 0);
//	r1 = printf("%010.3d\n", 0);
//	r1 = printf("%03*.3d\n", 10, 0);
//
//	r1 = printf("%0*.10d\n", 3, 0);
//	r1 = printf("%03.10d\n", 0);
//	r1 = printf("%03*.10d\n", 3, 0);
}
