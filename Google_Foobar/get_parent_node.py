'''
2.1 Ion Flux Relabeling

Oh no! Commander Lambda's latest experiment to improve the efficiency of her 
LAMBCHOP doomsday device has backfired spectacularly. She had been improving the 
structure of the ion flux converter tree, but something went terribly wrong and 
the flux chains exploded. Some of the ion flux converters survived the explosion intact, 
but others had their position labels blasted off. She's having her henchmen rebuild the 
ion flux converter tree by hand, but you think you can do it much more quickly - 
quickly enough, perhaps, to earn a promotion!

Flux chains require perfect binary trees, so Lambda's design arranged the ion flux 
converters to form one. To label them, she performed a post-order traversal of the tree 
of converters and labeled each converter with the order of that converter in the traversal, 
starting at 1. For example, a tree of 7 converters would look like the following:

		7
	3		6
1		2 4		5	

Write a function answer(h, q) - where h is the height of the perfect tree of converters 
and q is a list of positive integers representing different flux converters - 
which returns a list of integers p where each element in p is the label of the converter 
that sits on top of the respective converter in q, or -1 if there is no such converter. 
For example, answer(3, [1, 4, 7]) would return the converters above the converters at 
indexes 1, 4, and 7 in a perfect binary tree of height 3, which is [3, 6, -1].

The domain of the integer h is 1 <= h <= 30, where h = 1 represents a perfect binary tree 
containing only the root, h = 2 represents a perfect binary tree with the root and two leaf 
nodes, h = 3 represents a perfect binary tree with the root, two internal nodes and four leaf 
nodes (like the example above), and so forth. The lists q and p contain at least one but no 
more than 10000 distinct integers, all of which will be between 1 and 2^h-1, inclusive.
'''



class binary_tree:
	def __init__(self, depth):
		self.depth = depth
		self.max_idx = pow(2, depth) - 1
	def get_parent(self, i):
		subtree_size = self.max_idx
		if (i >= subtree_size):
			return -1
		node_offset = 0
		while True:
			subtree_size >>= 1
			left = node_offset + subtree_size
			right = left + subtree_size
			if (i == left or i == right):
				return right + 1
			if i > left:
				node_offset = left


def get_parents(h, q):
	bt = binary_tree(h)
#	r = []
#	for i in q:
#		r.append(bt.get_parent(i))
#	return r
	return [ bt.get_parent(i) for i in q ]

h = 5
q = [19, 14, 28, 31, 30]
print(get_parents(h,q))