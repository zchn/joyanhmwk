void main()
{
  int i;
  i = 1;
  while(1)
  {
    printf(i);
    i = i + 1;
    if(i >= 10) break;
    else continue; 
  }
  while(i > 0)
  {
    printf(i);
    i = i - 1;
  }
  println();
}
