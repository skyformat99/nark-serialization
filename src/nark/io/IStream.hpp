/* vim: set tabstop=4 : */
#ifndef __nark_io_IStream_h__
#define __nark_io_IStream_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/bool.hpp>
#include <stdio.h> // for getFILE
#include "../stdtypes.hpp"

namespace nark {

class FEBIRD_DLL_EXPORT ISeekable
{
public:
	typedef boost::mpl::true_ is_seekable;

	virtual ~ISeekable();
	virtual void rewind();
	virtual void seek(stream_position_t position);
	virtual void seek(stream_offset_t offset, int origin) = 0;
	virtual stream_position_t tell() const = 0;
	virtual stream_position_t size() const = 0;
};

class FEBIRD_DLL_EXPORT IInputStream
{
public:
	typedef boost::mpl::false_ is_seekable;

	virtual ~IInputStream();

	virtual size_t read(void* vbuf, size_t length) = 0;

	/**
	 @brief End Of File

	  only InputStream has eof() mark, OutputStream does not have eof()
	 */
	virtual bool eof() const = 0;

#ifdef _GNU_SOURCE
	FILE* forInputFILE();
#endif
};

class FEBIRD_DLL_EXPORT IOutputStream
{
public:
	typedef boost::mpl::false_ is_seekable;

	virtual ~IOutputStream();

	virtual size_t write(const void* vbuf, size_t length) = 0;
	virtual void flush() = 0;

#ifdef _GNU_SOURCE
	FILE* forOutputFILE();
#endif
};

class FEBIRD_DLL_EXPORT IDuplexStream : public IInputStream, public IOutputStream
{
public:
	typedef boost::mpl::false_ is_seekable;
};

class FEBIRD_DLL_EXPORT ISeekableInputStream : public ISeekable, public IInputStream
{
public:
   	typedef boost::mpl::true_ is_seekable;
	virtual size_t pread(stream_position_t pos, void* vbuf, size_t length);
};
class FEBIRD_DLL_EXPORT ISeekableOutputStream : public ISeekable, public IOutputStream
{
public:
   	typedef boost::mpl::true_ is_seekable;
	virtual size_t pwrite(stream_position_t pos, const void* vbuf, size_t length);
};
class FEBIRD_DLL_EXPORT ISeekableStream : public ISeekable, public IInputStream, public IOutputStream
{
public:	typedef boost::mpl::true_ is_seekable;
	virtual size_t pread(stream_position_t pos, void* vbuf, size_t length);
	virtual size_t pwrite(stream_position_t pos, const void* vbuf, size_t length);
};

class FEBIRD_DLL_EXPORT IAcceptor
{
public:
	virtual ~IAcceptor();
	virtual IDuplexStream* accept() = 0;
};

} // namespace nark

#endif

