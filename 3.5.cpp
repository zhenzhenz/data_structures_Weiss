List Union(List l, List p)
{
	List result;
	result = MakeEmpty();
	Position rp = result;
	Position lp = l->_next, pp = p->_next;
	while (lp != NULL&&pp != NULL)
	{
		if (lp->_element > pp->_element)
		{
			Insert(pp->_element, result, rp);
			rp = rp->_next;
			pp = pp->_next;
		}
		else if (lp->_element < pp->_element)
		{
			Insert(lp->_element, result, rp);
			rp = rp->_next;
			lp = lp->_next;
		}
		else
		{
			Insert(pp->_element, result, rp);
			rp = rp->_next;
			pp = pp->_next;
			lp = lp->_next;
		}
	}
	Position final;
	if (pp != NULL)
		final = pp;
	else if (lp != NULL)
		final = lp;
	else
		return result;
	while (final != NULL)
	{
		Insert(final->_element, result, rp);
		rp = rp->_next;
		final = final->_next;
	}
	return result;
}
