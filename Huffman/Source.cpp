#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ctnode
{
public:
	char letter;
	char mark;
	int info;
	ctnode *pright;
	ctnode *pleft;
};
class cbstree
{
public:
	ctnode *proot;
public:
	cbstree()
	{
		proot = NULL;
	}
	~cbstree()
	{
		Goodbye(proot);
	};
	void Goodbye(ctnode *ptrav)
	{
		if (ptrav == NULL)
			return;
		Goodbye(ptrav->pleft);
		Goodbye(ptrav->pright);
		delete ptrav;
	}
	void insert(ctnode *pnn)
	{
		if (proot == NULL)
			proot = pnn;
		else
		{
			ctnode *pb = NULL;
			ctnode *ptrav = proot;
			while (ptrav)
			{
				pb = ptrav;
				if (pnn->info > ptrav->info)
					ptrav = ptrav->pright;
				else
					ptrav = ptrav->pleft;
			}
			if (pnn->info > pb->info)
				pb->pright = pnn;
			else
				pb->pleft = pnn;
		}
	}
	void dispall(ctnode *ptrav)
	{
		if (ptrav == NULL)
			return;
		dispall(ptrav->pleft);
		cout << ptrav->info;
		dispall(ptrav->pright);
	}
	void disp()
	{
		dispall(proot);
	}
};
class cnode
{
public:
	char letter;
	char tmpmark;
	char let;
	string bin;
	int info;
	ctnode *tmp;
	cnode *pnext;
};
class clist
{
public:
	cnode *phead;
	cnode *ptail;
public:
	clist()
	{
		phead = NULL;
		ptail = NULL;
	}
	/*
	~clist()
	{
	cnode *ptrav;
	while (phead != NULL)
	{
	ptrav = phead;
	phead = phead->pnext;
	delete ptrav->tmp;
	delete ptrav;
	}
	}
	*/
	void insert(cnode *pnn)
	{
		if (phead == NULL)
			phead = pnn;
		else
		{
			cnode *pb = NULL;
			cnode *ptrav = phead;
			while (ptrav)
			{
				if (ptrav->info > pnn->info)
				{
					break;
				}
				pb = ptrav;
				ptrav = ptrav->pnext;
			}
			if (pb)
				pb->pnext = pnn;
			else
				phead = pnn;
			pnn->pnext = ptrav;
		}

	}
	void dispall()
	{
		cnode*ptrav;
		ptrav = phead;
		while (ptrav != NULL)
		{
			cout << ptrav->letter << "| ";
			cout << ptrav->info << " , ";
			cout << endl;
			ptrav = ptrav->pnext;
		}
		cout << endl;

	}
	void remove(int tv)
	{
		cnode *pb = NULL;
		cnode *ptrav = phead;
		while (ptrav != NULL)
		{
			if (ptrav->info == tv)
			{
				break;
			}
			pb = ptrav;
			ptrav = ptrav->pnext;
		}
		if (pb != NULL)
		{
			pb->pnext = ptrav->pnext;
			if (ptrav == ptail)
			{
				ptail = pb;
			}
		}
		else
		{
			phead = ptrav->pnext;
		}
		delete ptrav;
	}
};
void countletters(char letter[], clist &l, int length)
{
	char tmp;
	cnode *pnn;
	cnode *ptrav;
	int j = 0, ct = 0, flag = 0;
	int i = 0;

	while (j< length)
	{
		tmp = letter[j];
		ct = 0;
		int i = 0;
		ptrav = l.phead;
		flag = 0;
		// do not count the same letter twice
		while (ptrav)
		{
			if (ptrav->letter == tmp)
			{
				flag = 1;
				break;
			}
			ptrav = ptrav->pnext;
		}
		if (flag == 0)
		{
			//count letters
			while (i < length)
			{
				if (tmp == letter[i])
				{
					ct++;
				}
				i++;
			}
			pnn = new cnode;
			pnn->pnext = NULL;
			pnn->info = ct;
			pnn->letter = tmp;
			l.insert(pnn);

		}

		j++;
	}
}
ctnode *buildtree(clist l)
{
	int i = 0, tot = 0, f, f2 = 0;
	cnode *pb, *ptrav, *addagain;
	ctnode *pnn, *pnn2, *pnn3, *proot = NULL;
	ptrav = l.phead;
	while (ptrav)
	{
		tot += ptrav->info;
		ptrav = ptrav->pnext;
	}

	while (1)
	{
		f = 0;
		f2 = 0;
		ptrav = l.phead;
		if (ptrav)
		{
			pb = ptrav;
			ptrav = ptrav->pnext;
		}
		else
			break;
		pnn = new ctnode;
		pnn->pleft = NULL;
		pnn->pright = NULL;
		if (pb->tmpmark == '@'&&ptrav->tmpmark == '@')
		{
			pnn->pleft = pb->tmp;
			pnn->pright = ptrav->tmp;
			pnn->info = pb->info + ptrav->info;
			pnn->mark = '$';
			proot = pnn;
			f = 1;
		}
		pnn2 = new ctnode;
		pnn2->pleft = NULL;
		pnn2->pright = NULL;
		pnn2->letter = pb->letter;
		pnn2->info = pb->info;


		pnn3 = new ctnode;
		pnn3->pleft = NULL;
		pnn3->pright = NULL;
		pnn3->letter = ptrav->letter;
		pnn3->info = ptrav->info;

		if (f == 0)
		{
			if (pb->tmpmark == '@')
			{
				pnn->pleft = pb->tmp;
				pnn->pright = pnn3;
				pnn->info = pb->info + pnn3->info;
				pnn->mark = '$';
				proot = pnn;
				f2 = 1;
				f = 1;
			}
			if (f2 == 0)
			{
				if (ptrav->tmpmark == '@')
				{
					pnn->pleft = ptrav->tmp;
					pnn->pright = pnn2;
					pnn->info = ptrav->info + pnn2->info;
					pnn->mark = '$';
					proot = pnn;
					f = 1;
				}
			}

		}

		//remove the old
		l.remove(pb->info);
		l.remove(ptrav->info);
		if (f == 0)
		{
			pnn->pleft = pnn2;
			pnn->pright = pnn3;
			pnn->info = pnn3->info + pnn2->info;
			pnn->mark = '$';
			proot = pnn;
		}
		if (pnn->info == tot&&f == 1)
			break;
		// add again to the sorted list
		addagain = new cnode;
		addagain->pnext = NULL;
		addagain->info = pnn->info;
		addagain->tmpmark = '@';
		addagain->tmp = pnn;
		l.insert(addagain);
	}
	return proot;
}
void codeletters(ctnode *proot, string str, ofstream &index)
{
	if (proot == NULL)
		return;
	if (proot->mark != '$')
	{
		cout << proot->letter << "| " << str << endl;
		index.write(&proot->letter, 1 * sizeof(char));
		index << '|';
		index << str;
		index << '|';
	}
	codeletters(proot->pleft, str + "0", index);
	codeletters(proot->pright, str + "1", index);

}
void compress(char letters[], clist l2, int length, ofstream &comp_file)
{
	int i = 0, x, l = 0;
	char m = 1;
	char tofile = 0;
	char z = 0;
	int bit[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	int pos = 0, tot = 0;
	cnode *ptrav;
	while (i < length)
	{
		ptrav = l2.phead;
		while (ptrav)
		{
			if (ptrav->let == letters[i])
				break;
			ptrav = ptrav->pnext;
		}
		x = 0;
		if (ptrav != NULL)
		{

			while (x < ptrav->bin.length())
			{
				if (pos == 8)
				{
					pos = 0;
					z = 0;
					tofile = tot;
					comp_file.write(&tofile, 1 * sizeof(char));
					//cout << tot << endl;
					l++;
					tot = 0;
				}
				if (ptrav->bin[x] == '1')
				{
					z = z | (m << pos);
					tot += bit[pos];
				}
				pos++;
				x++;
			}
		}
		i++;
	}
	if (pos <= 8)
	{
		tofile = tot;
		comp_file.write(&tofile, 1 * sizeof(char));
		//cout << tot<<endl;
		l++;
	}
}
void decompress(char compressed[], clist l2, int length, int comp_len, ofstream &decomp)
{
	int i = 0, x, l, k, ct = 0, ct2 = 0, y = 2;
	char z;
	char m = 1;
	char res;
	string check;
	cnode *ptrav;
	while (i < comp_len)
	{
		z = compressed[i];
		x = 0;
		while (x<8)
		{
			res = z&(m << x);
			if (res != 0)
			{
				check += "1";
			}
			else
			{
				check += "0";
			}
			ptrav = l2.phead;
			while (ptrav)
			{
				l = 0;
				ct = 0;
				k = 0;
				while (l < ptrav->bin.length())
				{
					if (ptrav->bin[l] == check[k])
					{
						ct++;
						if (k<check.length())
							k++;
					}
					l++;
				}

				if (ct == ptrav->bin.length())
				{
					if (ct2 < length)
					{

						decomp << ptrav->let;
						ct2++;
					}
					check.clear();
				}
				ptrav = ptrav->pnext;

			}
			x++;
		}
		i++;
	}
	cout << endl;
}
void get_compressed(ifstream& get_comp, char *&compressed, int &comp_len)
{
	get_comp.seekg(0, get_comp.end);
	comp_len = get_comp.tellg();
	get_comp.seekg(0, get_comp.beg);
	compressed = new char[comp_len];
	//file to char array
	int i = 0;
	while (i < comp_len)
	{
		get_comp.read(&compressed[i], 1 * sizeof(char));
		i++;
	}
}
void get_index(clist &l2, ifstream& index)
{
	char *ind;
	int i = 0, f = 0;
	index.seekg(0, index.end);
	int length = index.tellg();
	index.seekg(0, index.beg);
	ind = new char[length];
	//file to char array
	while (i < length)
	{
		index.read(&ind[i], 1 * sizeof(char));
		i++;
	}

	for (i = 0; i < length; i++)
	{
		cnode *pnn = new cnode;
		pnn->pnext = NULL;
		pnn->tmp = NULL;
		pnn->info = 0;
		pnn->let = ind[i];
		i++;
		if (ind[i] == '|')
		{
			f = 1;
			i++;
		}
		if (f == 1)
		{
			while (ind[i] != '|')
			{
				pnn->bin += ind[i];
				i++;
				f = 0;
			}
		}
		l2.insert(pnn);
	}
	delete ind;
}
void main()
{
	ifstream file("hi.txt", std::ifstream::binary);
	ofstream comp_file("compressed.txt", std::ifstream::binary);
	ofstream index("index.txt", std::ifstream::binary);
	ofstream decomp("decompressed.txt", std::ifstream::binary);
	string tmp;
	ctnode *proot;
	char *letters;
	char *compressed;
	clist l, l2;
	//cbstree
	int i = 0;
	int count = 0;
	int ct = 0;
	int comp_len = 0;
	// get length of file:
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	letters = new char[length];
	//file to char array
	while (i < length)
	{
		file.read(&letters[i], 1 * sizeof(char));
		i++;
	}
	countletters(letters, l, length);
	l.dispall();
	proot = buildtree(l);
	codeletters(proot, tmp, index);
	index.close();
	ifstream index2("index.txt", std::ifstream::binary);
	get_index(l2, index2);
	compress(letters, l2, length, comp_file);
	comp_file.close();
	ifstream get_comp("compressed.txt", std::ifstream::binary);
	get_compressed(get_comp, compressed, comp_len);
	decompress(compressed, l2, length, comp_len, decomp);
	system("pause");
	file.close();
	comp_file.close();
	get_comp.close();
	delete letters;
}