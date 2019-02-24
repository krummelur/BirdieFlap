//BORROWED FROM https://stackoverflow.com/questions/11819837/converting-integer-to-string-in-c-without-sprintf
int integer_to_string(char *buf, int bufsize, int n)
{
   char *start;

   // Handle negative numbers.
   //
   if (n < 0)
   {
      if (!bufsize)
         return -1;

      *buf++ = '-';
      bufsize--;
   }

   // Remember the start of the string...  This will come into play
   // at the end.
   //
   start = buf;

   do
   {
      // Handle the current digit.
      //
      int digit;
      if (!bufsize)
         return -1;
      digit = n % 10;
      if (digit < 0)
         digit *= -1;
      *buf++ = digit + '0';
      bufsize--;
      n /= 10;
   } while (n);

   // Terminate the string.
   //
   if (!bufsize)
      return -1;
   *buf = 0;

   // We wrote the string backwards, i.e. with least significant digits first.
   // Now reverse the string.
   //
   --buf;
   while (start < buf)
   {
      char a = *start;
      *start = *buf;
      *buf = a;
      ++start;
      --buf;
   }

   return 0;
}