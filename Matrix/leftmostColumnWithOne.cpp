/* LC#1428

A row-sorted binary matrix means 
that all elements are 0 or 1 
and each row of the matrix is sorted 
in non-decreasing order.

Given a row-sorted binary matrix binaryMatrix, 
return the index (0-indexed) of the leftmost column 
with a 1 in it. 
If such an index does not exist, return -1.

You can't access the Binary Matrix directly. 
You may only access the matrix using a BinaryMatrix interface:

BinaryMatrix.get(row, col) returns 
the element of the matrix at index (row, col) (0-indexed).

BinaryMatrix.dimensions() returns 
the dimensions of the matrix as a list of 2 elements 
[rows, cols], which means the matrix is rows x cols.

For custom testing purposes, 
the input will be the entire binary matrix mat. 
You will not have access to the binary matrix directly.
*/

int searchOne (BinaryMatrix &binaryMatrix, int row, int col) {
	int left = 0, right = col - 1;
    while (left < right) {
		if (right - left == 1 
			&& binaryMatrix.get(row, left) == 0 
			&& binaryMatrix.get(row, right) == 0)
			return -1;
		if (right - left == 1 
			&& binaryMatrix.get(row, left) == 0 
			&& binaryMatrix.get(row, right) == 1)
			return right;
		if (right - left == 1 
			&& binaryMatrix.get(row, left) == 1)
			return left;
		int mid = (left + right) / 2;
		if (binaryMatrix.get(row, mid) == 1)
			right = mid;
		else
			left = mid;
	}
	return -1;
}

int leftMostColumnWithOne (BinaryMatrix &binaryMatrix) {
	vector<int> dim = binaryMatrix.dimensions();
	int res = -1;
	for (int i = 0; i < dim[0]; i++) {
		int leftmostOne = searchOne(binaryMatrix, i, dim[1]);
		if (leftmostOne != -1 && res == -1)
			res = leftmostOne;
		else if (leftmostOne != -1 && res != -1)
			res = min(res, leftmostOne);
	}
	return res;
}