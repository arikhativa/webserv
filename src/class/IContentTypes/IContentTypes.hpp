#ifndef I_CONTENT_TYPES_HPP
#define I_CONTENT_TYPES_HPP

#include <list>
#include <string>
#include <iostream>
#include <map>


#ifdef TEST_ON
#define private public
#define protected public
#endif

class IContentTypes
{
  protected:
	std::map<std::string, std::string> _content_types;
  public:
	virtual ~IContentTypes(){};
	IContentTypes()
	{
		_content_types[".html"] = "text/html";
		_content_types[".htm"] = "text/html";
		_content_types[".shtml"] = "text/html";
		_content_types[".css"] = "text/css";
		_content_types[".xml"] = "text/xml";
		_content_types[".gif"] = "image/gif";
		_content_types[".jpeg"] = "image/jpeg";
		_content_types[".jpg"] = "image/jpeg";
		_content_types[".js"] = "application/javascript";
		_content_types[".atom"] = "application/atom+xml";
		_content_types[".rss"] = "application/rss+xml";

		_content_types[".mml"] = "text/mathml";
		_content_types[".txt"] = "text/plain";
		_content_types[".jad"] = "text/vnd.sun.j2me.app-descriptor";
		_content_types[".wml"] = "text/vnd.wap.wml";
		_content_types[".htc"] = "text/x-component";

		_content_types[".png"] = "image/png";
		_content_types[".svg"] = "image/svg+xml";
		_content_types[".svgz"] = "image/svg+xml";
		_content_types[".tif"] = "image/tiff";
		_content_types[".tiff"] = "image/tiff";
		_content_types[".wbmp"] = "image/vnd.wap.wbmp";
		_content_types[".webp"] = "image/webp";
		_content_types[".ico"] = "image/x-icon";
		_content_types[".jng"] = "image/x-jng";
		_content_types[".bmp"] = "image/x-ms-bmp";

		_content_types[".woff"] = "font/woff";
		_content_types[".woff2"] = "font/woff2";

		_content_types[".jar"] = "application/java-archive";
		_content_types[".war"] = "application/java-archive";
		_content_types[".ear"] = "application/java-archive";
		_content_types[".json"] = "application/json";
		_content_types[".hqx"] = "application/mac-binhex40";
		_content_types[".doc"] = "application/msword";
		_content_types[".pdf"] = "application/pdf";
		_content_types[".ps"] = "application/postscript";
		_content_types[".eps"] = "application/postscript";
		_content_types[".ai"] = "application/postscript";
		_content_types[".rtf"] = "application/rtf";
		_content_types[".m3u8"] = "application/vnd.apple.mpegurl";
		_content_types[".kml"] = "application/vnd.google-earth.kml+xml";
		_content_types[".kmz"] = "application/vnd.google-earth.kmz";
		_content_types[".xls"] = "application/vnd.ms-excel";
		_content_types[".eot"] = "application/vnd.ms-fontobject";
		_content_types[".ppt"] = "application/vnd.ms-powerpoint";
		_content_types[".odg"] = "application/vnd.oasis.opendocument.graphics";
		_content_types[".odp"] = "application/vnd.oasis.opendocument.presentation";
		_content_types[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
		_content_types[".odt"] = "application/vnd.oasis.opendocument.text";

		_content_types[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
		_content_types[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
		_content_types[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";

		_content_types[".wmlc"] = "application/vnd.wap.wmlc";
		_content_types[".7z"] = "application/x-7z-compressed";
		_content_types[".cco"] = "application/x-cocoa";
		_content_types[".jardiff"] = "application/x-java-archive-diff";
		_content_types[".jnlp"] = "application/x-java-jnlp-file";
		_content_types[".run"] = "application/x-makeself";
		_content_types[".pl"] = "application/x-perl";
		_content_types[".pm"] = "application/x-perl";
		_content_types[".prc"] = "application/x-pilot";
		_content_types[".pdb"] = "application/x-pilot";
		_content_types[".rar"] = "application/x-rar-compressed";
		_content_types[".rpm"] = "application/x-redhat-package-manager";
		_content_types[".sea"] = "application/x-sea";
		_content_types[".swf"] = "application/x-shockwave-flash";
		_content_types[".sit"] = "application/x-stuffit";
		_content_types[".tcl"] = "application/x-tcl";
		_content_types[".tk"] = "application/x-tcl";
		_content_types[".der"] = "application/x-x509-ca-cert";
		_content_types[".pem"] = "application/x-x509-ca-cert";
		_content_types[".crt"] = "application/x-x509-ca-cert";
		_content_types[".xpi"] = "application/x-xpinstall";
		_content_types[".xhtml"] = "application/xhtml+xml";
		_content_types[".xspf"] = "application/xspf+xml";
		_content_types[".zip"] = "application/zip";

		_content_types[".bin"] = "application/octet-stream";
		_content_types[".exe"] = "application/octet-stream";
		_content_types[".dll"] = "application/octet-stream";
		_content_types[".deb"] = "application/octet-stream";
		_content_types[".dmg"] = "application/octet-stream";
		_content_types[".iso"] = "application/octet-stream";
		_content_types[".img"] = "application/octet-stream";
		_content_types[".msi"] = "application/octet-stream";
		_content_types[".msp"] = "application/octet-stream";
		_content_types[".msm"] = "application/octet-stream";

		_content_types[".mid"] = "audio/midi";
		_content_types[".midi"] = "audio/midi";
		_content_types[".kar"] = "audio/midi";
		_content_types[".mp3"] = "audio/mpeg";
		_content_types[".ogg"] = "audio/ogg";
		_content_types[".m4a"] = "audio/x-m4a";
		_content_types[".ra"] = "audio/x-realaudio";

		_content_types[".3gpp"] = "video/3gpp";
		_content_types[".3gp"] = "video/3gpp";
		_content_types[".ts"] = "video/mp2t";
		_content_types[".mp4"] = "video/mp4";
		_content_types[".mpeg"] = "video/mpeg";
		_content_types[".mpg"] = "video/mpeg";
		_content_types[".mov"] = "video/quicktime";
		_content_types[".webm"] = "video/webm";
		_content_types[".flv"] = "video/x-flv";
		_content_types[".m4v"] = "video/x-m4v";
		_content_types[".mng"] = "video/x-mng";
		_content_types[".asx"] = "video/x-ms-asf";
		_content_types[".asf"] = "video/x-ms-asf";
		_content_types[".wmv"] = "video/x-ms-wmv";
		_content_types[".avi"] = "video/x-msvideo";
	};
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_CONTENT_TYPES_HPP */
