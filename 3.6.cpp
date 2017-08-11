List add(List a, List b)
{
	List result;
	result = MakeEmpty();
	List ha = a->_next;
	List hb = b->_next;
	while (ha != NULL&&hb != NULL)
	{
		if (ha->_exp > hb->_exp)
		{
			pushBack(ha->_coe, ha->_exp, result);
			ha = ha->_next;
		}
		else if (ha->_exp < hb->_exp)
		{
			pushBack(hb->_coe, hb->_exp, result);
			hb = hb->_next;
		}
		else
		{
			pushBack(ha->_coe + hb->_coe, ha->_exp + hb->_exp, result);
			ha = ha->_next;
			hb = hb->_next;
		}
	}

	if (ha != NULL)
	{
		while (ha != NULL)
		{
			pushBack(ha->_coe, ha->_exp, result);
			ha = ha->_next;
		}
	}
	else if (hb != NULL)
	{
		while (hb != NULL)
		{
			pushBack(hb->_coe, hb->_exp, result);
			hb = hb->_next;
		}
	}

	return result;
}