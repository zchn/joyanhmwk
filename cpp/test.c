struct bb
{
	int a;
	int b[10][2];
};
void func(int a,int b[10][2])
{
	b[9][1] = 1;
	printf(a);
	println();
	
}
void main()
{
	struct bb b[5];
	b[2].b[9][1] = 10;
	func(b[2].b[9][1],b[2].b);
	printf(b[2].b[9][1]);
}
