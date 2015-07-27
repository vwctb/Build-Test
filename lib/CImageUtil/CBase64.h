#include <string.h>
#include <stdio.h>

class CBase64
{
	/************************************************************************/
	/*              Public Function											*/
	/************************************************************************/
public:

	CBase64();
	~CBase64();

	int Base64_Encode(char *dest, const char *src, int len);
	int Base64_Decode(char *dest, const char *src);
	int Base64_DecodeLen(const char *src);

	/************************************************************************/
	/*              Protected Function										*/
	/************************************************************************/
private:

	void Encode_group(unsigned char output[], const unsigned char input[], int n);
	void Decode_Group(unsigned char output[], const unsigned char input[], int *n);

	unsigned char m_b64_tbl[256];
	unsigned char m_b64_pad;

	/************************************************************************/
	/*              Protected Member										*/
	/************************************************************************/
private:

};
