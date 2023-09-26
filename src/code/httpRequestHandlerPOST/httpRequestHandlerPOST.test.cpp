
#include <httpRequestHandlerPOST/httpRequestHandlerPOST.hpp>
#include <gtest/gtest.h>

TEST(httpRequestHandlerPOST, simple)
{
	std::string requesetUpload = "POST /upload HTTP/1.1
Host: localhost:1234
Connection: keep-alive
Content-Length: 217
Cache-Control: max-age=0
sec-ch-ua: "Not.A/Brand";v="8", "Chromium";v="114"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "Linux"
Upgrade-Insecure-Requests: 1
Origin: http://localhost:1234
Content-Type: multipart/form-data; boundary=----WebKitFormBoundarygkhYA906SpBkcY3W
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Referer: http://localhost:1234/pepe.html
Accept-Encoding: gzip, deflate, br
Accept-Language: en-US,en;q=0.9

------WebKitFormBoundarygkhYA906SpBkcY3W
Content-Disposition: form-data; name="filename"; filename="wordlist"
Content-Type: application/octet-stream

drowsiness
epepe

------WebKitFormBoundarygkhYA906SpBkcY3W--";
	
	
}