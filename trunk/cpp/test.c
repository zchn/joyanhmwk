/* ¿ØÖÆÓï¾ä-for */

void main()
{
  int i, j;
  for(i=1;i<=10;i=i+1)
    printf(i);
  println();
  for(i=1;;i=i+1)
  {
    printf(i);
    if(i >= 10) break;
  }
  println();
  for(;i>=-10;i=i-1)
  {
    if(i > 0) continue;
    printf(i);
  }
  println();
  j = 0;
println();
  for(;;)
  {
    j = j + i % 2;
    i = i / 2;
	printf(i);
    if(i == 0) break;  
  }
  printf(j);
  println();
}