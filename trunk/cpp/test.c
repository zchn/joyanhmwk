int max(int a,int b)
{
	if (a>=b)
		return a;
	return b;
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
	int i;
	i = 1;
	while(i < 10){
		a = a+1;
		i = i+1;
		printf(a);
	}
	printf(11111111);
        b=55728;
	struc[10].b.m = 135;
	struc[10].c.m = 137;
	printf(max(b,a));
	printf(max(a,b));
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
	c = 1 || (a = 21);
	printf(c);
	printf(a);
	c = 0 && (a = 21);
	printf(c);
        printf(a);
        c = 1 && (a = 21);
        printf(c);
        printf(a);
}
        
