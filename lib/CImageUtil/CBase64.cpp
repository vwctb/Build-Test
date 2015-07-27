
#include "CBase64.h"

CBase64::CBase64()
{
	strcpy((char *)m_b64_tbl,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
	m_b64_pad = '=';
}

CBase64::~CBase64()
{
}

int CBase64::Base64_Encode(char *dest, const char *src, int len)
{
	int outsz = 0;

	while (len > 0) 
	{
		Encode_group((unsigned char *)dest + outsz, (const unsigned char *)src, len > 3 ? 3 : len);
		len -= 3;
		src += 3;
		outsz += 4;
	}

	return outsz;
}

int CBase64::Base64_Decode(char *dest, const char *src)
{
	int len;
	int outsz = 0;

	while (*src) 
	{
		Decode_Group((unsigned char *)dest + outsz, (const unsigned char *)src, &len);
		src += 4;
		outsz += len;
	}

	return outsz;
}

int CBase64::Base64_DecodeLen(const char *src)
{
	int len;
	int outsz = 0;
	unsigned char dest[10];

	while (*src) 
	{
		Decode_Group(dest,(const unsigned char *) src, &len);
		src += 4;
		outsz += len;
	}

	return outsz;
}

/* base64 encode a group of between 1 and 3 input chars into a group of
 * 4 output chars */
void CBase64::Encode_group(unsigned char output[], const unsigned char input[], int n)
{
        unsigned char ingrp[3];

        ingrp[0] = n > 0 ? input[0] : 0;
        ingrp[1] = n > 1 ? input[1] : 0;
        ingrp[2] = n > 2 ? input[2] : 0;

        /* upper 6 bits of ingrp[0] */
        output[0] = n > 0 ? m_b64_tbl[ingrp[0] >> 2] : m_b64_pad;
        /* lower 2 bits of ingrp[0] | upper 4 bits of ingrp[1] */
        output[1] = n > 0 ? m_b64_tbl[((ingrp[0] & 0x3) << 4) | (ingrp[1] >> 4)]
                : m_b64_pad;
        /* lower 4 bits of ingrp[1] | upper 2 bits of ingrp[2] */
        output[2] = n > 1 ? m_b64_tbl[((ingrp[1] & 0xf) << 2) | (ingrp[2] >> 6)]
                : m_b64_pad;
        /* lower 6 bits of ingrp[2] */
        output[3] = n > 2 ? m_b64_tbl[ingrp[2] & 0x3f] : m_b64_pad;

}


/* base64 decode a group of 4 input chars into a group of between 0 and
 * 3
 * output chars */
void CBase64::Decode_Group(unsigned char output[], const unsigned char input[], int *n)
{
        char *t1,*t2;
        *n = 0;

        if (input[0] == m_b64_pad)
                return;

        if (input[1] == m_b64_pad) {
                fprintf(stderr, "Warning: orphaned bits ignored.\n");
                return;
        }

        t1 = strchr((char *)m_b64_tbl, input[0]);
        t2 = strchr((char *)m_b64_tbl, input[1]);

        if ((t1 == NULL) || (t2 == NULL)) {
                fprintf(stderr, "Warning: garbage found, giving up.\n");
                return;
        }

        output[(*n)++] = (((unsigned char *)t1 - m_b64_tbl) << 2) | (((unsigned char *)t2 - m_b64_tbl) >> 4);

        if (input[2] == m_b64_pad)
                return;

        t1 = strchr((char *)m_b64_tbl, input[2]);

        if (t1 == NULL) {
                fprintf(stderr, "Warning: garbage found, giving up.\n");
                return;
        }

        output[(*n)++] = (((unsigned char *)t2 - m_b64_tbl) << 4) | (((unsigned char *)t1 - m_b64_tbl) >> 2);

        if (input[3] == m_b64_pad)
                return;

        t2 = strchr((char *)m_b64_tbl, input[3]);

        if (t2 == NULL) {
                fprintf(stderr, "Warning: garbage found, giving up.\n");
                return;
        }

        output[(*n)++] = (((unsigned char *)t1 - m_b64_tbl) << 6) | ((unsigned char *)t2 - m_b64_tbl);

        return;
}
