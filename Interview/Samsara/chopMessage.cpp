/*
Imagine that you are given some text 
that a user would like to send 
as a sequence of SMS messages. 
However, there is a limit 
specifying the maximum number of characters 
a single message can contain. 
Your task is to split all characters 
of text into the minimum number 
of SMS messages possible.

Each message must contain 
a part of the text, 
followed by the suffix <X/Y>, 
where Y is the total number of messages 
and X is the number of the current message 
(starting from 1). 
The suffix is considered to be 
a part of the message, 
so the total length of each message 
includes the length of the suffix. 
Only the last message in the sequence 
can be shorter than limit characters.

Iterate over all numbers of messages Y 
starting from 1. 
Remember to split text 
into as few SMS messages as possible. 
Return an array containing the sequence 
of SMS messages corresponding to this split. 
If it's not possible to split the text 
into different messages 
based on the limit, 
return an empty array.

Note: You are not expected to provide 
the most optimal solution, 
but a solution with time complexity 
not worse than O(text.length2) 
will fit within the execution time limit.
*/