#include <IContentTypes/IContentTypes.hpp>

std::map<std::string, std::string> IContentTypes::create_map()
{
	std::map<std::string, std::string> ret;
	ret[".html"] = "text/html";
		ret[".htm"] = "text/html";
		ret[".shtml"] = "text/html";
		ret[".css"] = "text/css";
		ret[".xml"] = "text/xml";
		ret[".gif"] = "image/gif";
		ret[".jpeg"] = "image/jpeg";
		ret[".jpg"] = "image/jpeg";
		ret[".js"] = "application/javascript";
		ret[".atom"] = "application/atom+xml";
		ret[".rss"] = "application/rss+xml";

		ret[".mml"] = "text/mathml";
		ret[".txt"] = "text/plain";
		ret[".jad"] = "text/vnd.sun.j2me.app-descriptor";
		ret[".wml"] = "text/vnd.wap.wml";
		ret[".htc"] = "text/x-component";

		ret[".png"] = "image/png";
		ret[".svg"] = "image/svg+xml";
		ret[".svgz"] = "image/svg+xml";
		ret[".tif"] = "image/tiff";
		ret[".tiff"] = "image/tiff";
		ret[".wbmp"] = "image/vnd.wap.wbmp";
		ret[".webp"] = "image/webp";
		ret[".ico"] = "image/x-icon";
		ret[".jng"] = "image/x-jng";
		ret[".bmp"] = "image/x-ms-bmp";

		ret[".woff"] = "font/woff";
		ret[".woff2"] = "font/woff2";

		ret[".jar"] = "application/java-archive";
		ret[".war"] = "application/java-archive";
		ret[".ear"] = "application/java-archive";
		ret[".json"] = "application/json";
		ret[".hqx"] = "application/mac-binhex40";
		ret[".doc"] = "application/msword";
		ret[".pdf"] = "application/pdf";
		ret[".ps"] = "application/postscript";
		ret[".eps"] = "application/postscript";
		ret[".ai"] = "application/postscript";
		ret[".rtf"] = "application/rtf";
		ret[".m3u8"] = "application/vnd.apple.mpegurl";
		ret[".kml"] = "application/vnd.google-earth.kml+xml";
		ret[".kmz"] = "application/vnd.google-earth.kmz";
		ret[".xls"] = "application/vnd.ms-excel";
		ret[".eot"] = "application/vnd.ms-fontobject";
		ret[".ppt"] = "application/vnd.ms-powerpoint";
		ret[".odg"] = "application/vnd.oasis.opendocument.graphics";
		ret[".odp"] = "application/vnd.oasis.opendocument.presentation";
		ret[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
		ret[".odt"] = "application/vnd.oasis.opendocument.text";

		ret[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
		ret[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
		ret[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";

		ret[".wmlc"] = "application/vnd.wap.wmlc";
		ret[".7z"] = "application/x-7z-compressed";
		ret[".cco"] = "application/x-cocoa";
		ret[".jardiff"] = "application/x-java-archive-diff";
		ret[".jnlp"] = "application/x-java-jnlp-file";
		ret[".run"] = "application/x-makeself";
		ret[".pl"] = "application/x-perl";
		ret[".pm"] = "application/x-perl";
		ret[".prc"] = "application/x-pilot";
		ret[".pdb"] = "application/x-pilot";
		ret[".rar"] = "application/x-rar-compressed";
		ret[".rpm"] = "application/x-redhat-package-manager";
		ret[".sea"] = "application/x-sea";
		ret[".swf"] = "application/x-shockwave-flash";
		ret[".sit"] = "application/x-stuffit";
		ret[".tcl"] = "application/x-tcl";
		ret[".tk"] = "application/x-tcl";
		ret[".der"] = "application/x-x509-ca-cert";
		ret[".pem"] = "application/x-x509-ca-cert";
		ret[".crt"] = "application/x-x509-ca-cert";
		ret[".xpi"] = "application/x-xpinstall";
		ret[".xhtml"] = "application/xhtml+xml";
		ret[".xspf"] = "application/xspf+xml";
		ret[".zip"] = "application/zip";

		ret[".bin"] = "application/octet-stream";
		ret[".exe"] = "application/octet-stream";
		ret[".dll"] = "application/octet-stream";
		ret[".deb"] = "application/octet-stream";
		ret[".dmg"] = "application/octet-stream";
		ret[".iso"] = "application/octet-stream";
		ret[".img"] = "application/octet-stream";
		ret[".msi"] = "application/octet-stream";
		ret[".msp"] = "application/octet-stream";
		ret[".msm"] = "application/octet-stream";

		ret[".mid"] = "audio/midi";
		ret[".midi"] = "audio/midi";
		ret[".kar"] = "audio/midi";
		ret[".mp3"] = "audio/mpeg";
		ret[".ogg"] = "audio/ogg";
		ret[".m4a"] = "audio/x-m4a";
		ret[".ra"] = "audio/x-realaudio";

		ret[".3gpp"] = "video/3gpp";
		ret[".3gp"] = "video/3gpp";
		ret[".ts"] = "video/mp2t";
		ret[".mp4"] = "video/mp4";
		ret[".mpeg"] = "video/mpeg";
		ret[".mpg"] = "video/mpeg";
		ret[".mov"] = "video/quicktime";
		ret[".webm"] = "video/webm";
		ret[".flv"] = "video/x-flv";
		ret[".m4v"] = "video/x-m4v";
		ret[".mng"] = "video/x-mng";
		ret[".asx"] = "video/x-ms-asf";
		ret[".asf"] = "video/x-ms-asf";
		ret[".wmv"] = "video/x-ms-wmv";
		ret[".avi"] = "video/x-msvideo";
		return (ret);
}

std::map<std::string, std::string> IContentTypes::_content_types = create_map();