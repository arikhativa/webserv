
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <cstdlib>
#include <iostream>
#include <string>

#include <AllowedMethods/AllowedMethods.hpp>
#include <CGIConf/CGIConf.hpp>
#include <ErrorPage/ErrorPage.hpp>
#include <ErrorPageSet/ErrorPageSet.hpp>
#include <IErrorPage/IErrorPage.hpp>
#include <ILocation/ILocation.hpp>
#include <IReturn/IReturn.hpp>
#include <OnOff/OnOff.hpp>
#include <Path/Path.hpp>
#include <Return/Return.hpp>
#include <Token/Token.hpp>
#include <converter/converter.hpp>
#include <listPrint/listPrint.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Location : public ILocation
{
  public:
	Location();
	virtual ~Location();

	void setDefaultSettingIfNeeded(void);

	virtual const IPath &getPath(void) const;
	virtual bool isAutoIndexOn(void) const;
	virtual bool canUpload(void) const;
	virtual std::size_t getMaxBodySize(void) const;
	virtual const IAllowedMethods &getAllowedMethods(void) const;
	virtual const IReturn *getReturn(void) const;
	virtual const std::list< std::string > &getIndexFiles(void) const;
	virtual std::list< const IErrorPage * > getErrorPages(void) const;
	virtual const IPath *getRoot(void) const;
	virtual const IPath *getUploadPath(void) const;
	virtual const CGIConf &getCGIConf(void) const;
	virtual const ErrorPageSet &getErrorPageSet(void) const;

	bool isMaxBodySizeOn(void) const;

	void setPath(const std::string &path);
	void setAutoIndex(const std::string &auto_index);
	void setUpload(const std::string &upload);
	void setMaxBodySize(const std::string &max_body_size);
	void setAllowedMethods(const std::list< std::string > &allowed_methods);
	void setReturn(const std::string &status, const std::string &path);
	void setIndexFiles(const std::list< std::string > &index_files);
	void addErrorPage(const std::string &status, const std::string &path);
	void setRoot(const std::string &root);
	void setCGI(const std::string &ext, const std::string &path);
	void setUploadStore(const std::string &upload_store);

	class InvalidLocationException : public std::exception
	{
	  public:
		explicit InvalidLocationException(const std::string &msg);
		virtual ~InvalidLocationException() throw();
		virtual const char *what() const throw();

	  private:
		std::string _msg;
	};

  private:
	Path *_path;
	OnOff< bool > _auto_index;
	OnOff< bool > _upload;
	OnOff< std::size_t > _max_body_size;
	AllowedMethods *_allowed_methods;
	Return *_return;
	std::list< std::string > _index_files;
	std::list< ErrorPage > _error_pages;
	Path *_root;
	CGIConf _cgi;
	ErrorPageSet _error_pages_set;
	Path *_upload_store;

	void _initErrorPageSet(void);
};

std::ostream &operator<<(std::ostream &o, const Location &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* LOCATION_HPP */
