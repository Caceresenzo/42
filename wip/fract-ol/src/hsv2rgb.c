typedef struct
{
	char b; // a fraction between 0 and 1
	char g; // a fraction between 0 and 1
	char r; // a fraction between 0 and 1
	char a;
} rgb;

int
hsv2rgb(double in_h, double in_s, double in_v)
{
	double hh, p, q, t, ff;
	long i;
	rgb out;

	if (in_s <= 0.0)
	{ // < is bogus, just shuts up warnings
		out.r = in_v;
		out.g = in_v;
		out.b = in_v;
		return *((int*)&out);
	}
	hh = in_h;
	if (hh >= 360.0)
		hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = in_v * (1.0 - in_s);
	q = in_v * (1.0 - (in_s * ff));
	t = in_v * (1.0 - (in_s * (1.0 - ff)));
	switch (i)
	{
		case 0:
			out.r = in_v;
			out.g = t;
			out.b = p;
			break;
		case 1:
			out.r = q;
			out.g = in_v;
			out.b = p;
			break;
		case 2:
			out.r = p;
			out.g = in_v;
			out.b = t;
			break;
		case 3:
			out.r = p;
			out.g = q;
			out.b = in_v;
			break;
		case 4:
			out.r = t;
			out.g = p;
			out.b = in_v;
			break;
		case 5:
		default:
			out.r = in_v;
			out.g = p;
			out.b = q;
			break;
	}

	return *((int*)&out);
}
