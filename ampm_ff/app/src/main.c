
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stm32f10x.h>

#include "ampm_ff/ampm_ff.h"
#include "ampm_ff/ampm_ff_port.h"

const char *ca_cert = "\
	-----BEGIN CERTIFICATE-----\n\
MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCB\n\
yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL\n\
ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp\n\
U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW\n\
ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0\n\
aG9yaXR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjEL\n\
MAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZW\n\
ZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2ln\n\
biwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp\n\
U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9y\n\
aXR5IC0gRzUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1\n\
nmAMqudLO07cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbex\n\
t0uz/o9+B1fs70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIz\n\
SdhDY2pSS9KP6HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQG\n\
BO+QueQA5N06tRn/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+\n\
rCpSx4/VBEnkjWNHiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/\n\
NIeWiu5T6CUVAgMBAAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8E\n\
BAMCAQYwbQYIKwYBBQUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAH\n\
BgUrDgMCGgQUj+XTGoasjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVy\n\
aXNpZ24uY29tL3ZzbG9nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKv\n\
MzEzMA0GCSqGSIb3DQEBBQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzE\n\
p6B4Eq1iDkVwZMXnl2YtmAl+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y\n\
5gaRQBi5+MHt39tBquCWIMnNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlK\n\
WE9gyn6CagsCqiUXObXbf+eEZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ\n\
4fQRbxC1lfznQgUy286dUV4otp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8N\n\
hnacRHr2lVz2XTIIM6RUthg/aFzyQkqFOFSDX9HoLPKsEdao7WNq\n\
-----END CERTIFICATE-----\n\
";

const char *server_cert = "\
-----BEGIN CERTIFICATE-----\n\
MIIDWTCCAkGgAwIBAgIUWYCxn9tcU4UyrW1olimQCgU85BcwDQYJKoZIhvcNAQEL\n\
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n\
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE2MDEyOTE4MjMz\n\
N1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n\
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJwJA0KJ6EnDJv/uvm6C\n\
WTuUstTEebpaLzsjm/sjkjuJQdkcaotFlSAghhWGrX2QEzW+OqZ3d+61tWHuXBzn\n\
knFE1JxhsQN2xu9bFWGCXe8FFLg6n3vjH93JCG9JmAErCwzSjIm8xmX0nZFzVgk8\n\
AzMfqSQYZtguGJwKELGEZhMJrwmyM4v+DD+/fQbwyoxsp3tWQ9DmkR1dsvXfA2BA\n\
dkUsS3YC6jXRNimqGDAw+nllzWUM4TK4jQY1pNypVHKVth/15aSb3eLFJeWylv2M\n\
qnZDS3cdApiZ+ss+I6nHJPAMDkfQIPBsEnq/w1W4Umz5eRfuUZmz1fyfnF13U6f5\n\
YPcCAwEAAaNgMF4wHwYDVR0jBBgwFoAUkNH8iRp4miRwAJ9TS5ihy2CaDRMwHQYD\n\
VR0OBBYEFG+Y9RwubLZECJAORAIuIAlpsa2sMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n\
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAEfFw3d97C/lu7eathAqIEI3Hh\n\
+hWNHwn5OFvQDpseGL8cL6Nilawvb9ol3x2VMSg0UJTz7K+M5PsWu64l58TyJT1o\n\
g5oAJJTFGXf9eIyWvr4X4bndCHttlICMmuUmoknY9sMRBb8GR15v00z3pWaXmi+O\n\
qVqnPMRstKo0wdBgUsYsvtz2TZl2yDo0p5X/9YqDfWyjDhNGQFLE0e3dgqzWS+qg\n\
QmcKOR0dbp/SRDhg12l7pJKznVfgxabTtaadH5ZKhQHHGx2z9BMM88qdr5ifJL2I\n\
RDRWzFfR2WEyGEauP9X27MZRyQEqVNLOkP574K2sONlnS7zyNgDO7m9FzpcB\n\
-----END CERTIFICATE-----\n\
";

const char *server_key = "\
-----BEGIN RSA PRIVATE KEY-----\n\
MIIEowIBAAKCAQEAnAkDQonoScMm/+6+boJZO5Sy1MR5ulovOyOb+yOSO4lB2Rxq\n\
i0WVICCGFYatfZATNb46pnd37rW1Ye5cHOeScUTUnGGxA3bG71sVYYJd7wUUuDqf\n\
e+Mf3ckIb0mYASsLDNKMibzGZfSdkXNWCTwDMx+pJBhm2C4YnAoQsYRmEwmvCbIz\n\
i/4MP799BvDKjGyne1ZD0OaRHV2y9d8DYEB2RSxLdgLqNdE2KaoYMDD6eWXNZQzh\n\
MriNBjWk3KlUcpW2H/XlpJvd4sUl5bKW/YyqdkNLdx0CmJn6yz4jqcck8AwOR9Ag\n\
8GwSer/DVbhSbPl5F+5RmbPV/J+cXXdTp/lg9wIDAQABAoIBAGcD/Eb9zYKFeUYX\n\
VVqYbFlNvxOB8+v4hp5A0EZqIa103Sh9/kmc0uu3DU9A72GqsUQWJ5qn3WKYTPwu\n\
5lme+awWiVgFl1x2GrkEJYWPEH0xmZBYA9tDBFLk2tC+gcCjrlP03hxBqaq+aRkS\n\
UIcgO+yQxpayFZQ8OrsqWgMZKlr+TYh+2BhEhJrHadjR2uDpTDzG1DJp/l/n0/fz\n\
2um9fAnbfIO64tkDQkoH2WsuKS3+e7EOYLhH7EW5AT6OWzssBEKajItLv1fj1RvK\n\
7V6uSBc4EvoZOsLDviYQt0O+cMfBBVF6V7ZvDr7Q9dgpyv7sCiqvfCiNwuqpqvB8\n\
hqaADMECgYEA0SQRn8biYoVsbX9BJAPXREKFn982aoQ3qkWBzbysRN4ovBCw0NWu\n\
R88nr4nullivuX8QlZrSB08/MveW0b/75iv7UZHjeujh+Wu2URi5sBwzharF8Fye\n\
6kok/BMn8viQ5dNuFUH9ZtqU6/hFUxpN61QENZ8sYQE3BDuvE4DvI98CgYEAvv7m\n\
mk6hU3GxJ57/1ZDpwG6LGkTc2h7l+DfnJPHXazkyztmlFQWBUSdCRqWBJwUkTlt0\n\
G6cvaWZe8Dqa7+K4G9X6EBMMw/yvVprhsE/21wJIIhWiRzMpeA7X5ft0WxYGGPA1\n\
Nt443p2jA/5J3rrhFLH9PRZ3xOzBbbuL2+ItpekCgYBIfOLq6SkwEqSpMxEl5Xro\n\
OtJLvjcDJj6Q8rRx1bIz0Hh37qUKTPWyB/fuXLVoQObvOT5LTDT9uZbjGHOa0ZsC\n\
hT3/YLxirnMcWxv+8b3yb2PgMXeXvtKJzBcTk6QmD8dRET43ef7Vdm9ldlC45AYb\n\
yawH1dqw6JXkDre439iDKwKBgH4cfxV6P8mCM3Au60wP4FhgZVbWC2G2rzBDcUsS\n\
qKOy49pzGS6VMPrtyjQtiebC3WMjvbmYnZShtKQ4fh9Q+zHeCrxcZ7xs9zVfFRA+\n\
7ISxjAF9eWY74PDWFDZV31FZbHNBAFIXT0OmoIG9gPchPAdXMxgH4tNTZLDY+hMY\n\
9/0pAoGBAJSjYTNb/nnJuoH7MZKir0GdznXytPUgzWItxpZDZo0fkgglU8aoa4sM\n\
7tSnqXJXHPVO1OfSvHqFp5+FWjjNX4hu4wbzUkbupHRAQXlskhcr70mMEDnHGKWo\n\
15y/1G/bdvpMRmsKj6vi5p1wxrE7wKc/joYDhDbT5epI0hk+puOB\n\
-----END RSA PRIVATE KEY-----\n\
";

void SysSleep(void);
void SysInit(void);

enum{
	SYS_SLEEP_MODE,
	SYS_RUN_MODE
}sysStatus = SYS_RUN_MODE;


void HardFault_Handler(void)
{
	NVIC_SystemReset();
	while(1);
}

void SysInit(void)
{
	AMPM_FIL fil;
	AMPM_FIL *fil_win32;
	uint32_t i,j,len;
	uint8_t buf[32];
	//AMPM_FIL fsFile;
	__enable_irq();
	SystemInit();
	RCC->APB2ENR = (RCC_APB2ENR_AFIOEN |  /*enable clock for Alternate Function*/
								 RCC_APB2ENR_IOPAEN |  /* enable clock for GPIOA*/
								 RCC_APB2ENR_IOPBEN |	/*enable clock for GPIOB*/
								 RCC_APB2ENR_IOPCEN |/*enable clock for GPIOc*/ 									 
								 RCC_APB2ENR_IOPDEN	
								);   
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
	ampm_f_init();
	//ampm_f_disk_format();
	//FATFS
	if(ampm_f_open(&fil,"ca-cert.pem",AMPM_FA_READ) != FR_OK)
	{
		ampm_f_close(&fil);
		if(ampm_f_open(&fil,"ca-cert.pem",AMPM_FA_CREATE_ALWAYS) == FR_OK)
		{
			ampm_f_write(&fil,(char *)ca_cert,strlen(ca_cert),&i);
		}
	}
	ampm_f_close(&fil);
	//WIN32
	fil_win32 = ampm_fopen_win32("server-cert.pem","r");
	if(fil_win32 == NULL)
	{
		ampm_fclose_win32(fil_win32);
		fil_win32 = ampm_fopen_win32("server-cert.pem","w");
		if(fil_win32)
		{
			ampm_fwrite_win32((char *)server_cert,strlen(server_cert),1,fil_win32);
		}
	}
	ampm_fclose_win32(fil_win32);
	
	
	if(ampm_f_open(&fil,"server-key.pem",AMPM_FA_READ) != FR_OK)
	{
		ampm_f_close(&fil);
		if(ampm_f_open(&fil,"server-key.pem",AMPM_FA_CREATE_ALWAYS) == FR_OK)
		{
			ampm_f_write(&fil,(char *)server_key,strlen(server_key),&i);
		}
	}
	ampm_f_close(&fil);
}


int main(void)
{
	SysInit();
	while(1)
	{
	}
	return 0;
}

