-->					Redirection

good source for redirecting, here-doc...:
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_03


basic idea:
Perform redirection, remove redirection operators and operands from parameter list

- Used to open and close files fo the current shell execution environment
- Can be used with numbers representing file descriptors
- Failure to open or create a file sall cause a redirection to fail

[n]redir-operator word

>	redirection
>>	appending redirection

Here-Document = Shell Input File
-	treated as a single word that begins after the next \n and
continues until there is a line containing only the delimiter and a \n, with no blanks in between.
Then the next here-document starts, if there is one.
<<
<<-


possible edge cases:
if n is quoted, number shall not be recognized as part of the redirection expression