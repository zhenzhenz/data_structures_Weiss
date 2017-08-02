List Intersect(List l, List p)
{
	List result;
	result = MakeEmpty();
	Position rp = result;
	Position lp = l->_next, pp = p->_next;
	while (lp != NULL&&pp != NULL)
	{
		if (lp->_element > pp->_element)
			pp = pp->_next;
		else if (lp->_element < pp->_element)
			lp = lp->_next;
		else
		{
			Insert(pp->_element, result, rp);
			rp = rp->_next;
			pp = pp->_next;
			lp = lp->_next;
		}
	}

	return result;
}
