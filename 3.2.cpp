void PrintLots(List l, List p)
{
	int count = 1;
	Position pp = p->_next;
	Position lp = l->_next;
	if (pp == NULL || lp == NULL)
	{
		printf("Empty list!\n");
		return;
	}
	while (pp != NULL)
	{
		int target = pp->_element;
		while (count < target)
		{
			lp = lp->_next;
			++count;
		}
		printf("pp = %d,lp = %d\n", target, lp->_element);
		pp = pp->_next;
	}
}
