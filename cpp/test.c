int max(int a,int b)
{
	printf(a);
	printf(b);
	return (a>b)*a+(a<b)*b;
}
int main(int as,int bs)
{
        int a,b;
        int c,d;
	int arr[10];
	struct {
		struct str{
			int m;
		} b;
		int a[6];
		int mem;
		struct str c;
	} struc[18];
	struc[11].a[1] = 10;
	struc[11].mem = 102;
        a=312;
        b=55728;
	struc[10].b.m = 135;
	struc[10].c.m = 137;
	printf(max(b,a));
	printf(struc[10].b.m);
	printf(struc[10].c.m);
	printf(struc[11].mem);
	printf(a+b);
	arr[6] = 12345;
	c=a+b;
        d=a*(b+c);
	int k;
        printf(d);
	k=1;
	printf(k);
	printf(struc[11].a[1]);
	printf(arr[6]);
	max(a,b);
}
        
