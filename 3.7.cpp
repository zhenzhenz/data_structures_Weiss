//O(M*M*N)
List multi(List a, List b)
{
	List result = MakeEmpty();
	List ha = a->_next;
	
	while (ha != NULL)
	{
		List temp = MakeEmpty();
		List hb = b->_next;
		while (hb != NULL)
		{
			pushBack(ha->_coe * hb->_coe, ha->_exp + hb->_exp, temp);
			hb = hb->_next;
		}
		List current = add(result, temp);
		DeleteList(temp);
		DeleteList(result);
		result = current;
		ha = ha->_next;
		PrintList(result);
		printf("\n_______\n");
	}

	return result;
}