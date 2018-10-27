﻿#include "BearCore.hpp"
#include "tinyxml.h"
using namespace BearCore;
BearXML::BearXML():m_Doc(NULL)
{
}


BearCore::BearXML::~BearXML()
{
	clear();
}

bool BearCore::BearXML::loadFromFile(const bchar * file, BearString&value_error, BearString&out_error)
{
	clear();
	m_Doc = new TiXmlDocument;
	TiXmlDocument*m_doc = static_cast<TiXmlDocument*>(m_Doc);
	if (!m_doc->LoadFile(*BearEncoding::ToANSI(file)))
	{
		clear();
		return false;
	}
	if (m_doc->Error())
	{
#ifdef UNICODE
		value_error.assign(*BearEncoding::ToUTF16(m_doc->Value()));
		out_error.assign(*BearEncoding::ToUTF16(m_doc->ErrorDesc()));
#else
		value_error.assign(m_doc->Value());
		out_error.assign(m_doc->ErrorDesc());
#endif
		clear();
		return false;
	}
	return true;
}

bool BearCore::BearXML::loadFromStream(const BearInputStream & file, BearEncoding::Encoding tp, BearString&value_error, BearString&out_error)
{
	return loadFromBuffrer(BearMemoryStream(file), tp, value_error, out_error);
}

bool BearCore::BearXML::loadFromBuffrer(const BearBufferedReader & buffer, BearEncoding::Encoding tp, BearString&value_error, BearString&out_error)
{
	clear();
	m_Doc = new TiXmlDocument;
	TiXmlDocument*m_doc = static_cast<TiXmlDocument*>(m_Doc);

	if (tp == BearEncoding::ANSI)
	{
		auto ptr = BearEncoding::ToUTF8((const bchar8*)buffer.begin(), (const bchar8*)buffer.end());
		m_doc->Parse((char*)*ptr, 0, TIXML_ENCODING_UTF8);
		if (m_doc->Error())
		{
#ifdef UNICODE
			value_error.assign(*BearEncoding::ToUTF16(m_doc->Value()));
			out_error.assign(*BearEncoding::ToUTF16(m_doc->ErrorDesc()));
#else
			value_error.assign(m_doc->Value());
			out_error.assign(m_doc->ErrorDesc());
#endif
			clear();
			return false;
		}
	}
	else if (tp == BearEncoding::UTF16)
	{
		auto ptr = BearEncoding::ToUTF8((const bchar16*)buffer.begin(), (const bchar16*)buffer.end());
		m_doc->Parse((char*)*ptr, 0, TIXML_ENCODING_UTF8);
		if (m_doc->Error())
		{
#ifdef UNICODE
			value_error.assign(*BearEncoding::ToUTF16(m_doc->Value()));
			out_error.assign(*BearEncoding::ToUTF16(m_doc->ErrorDesc()));
#else
			value_error.assign(m_doc->Value());
			out_error.assign(m_doc->ErrorDesc());
#endif
			clear();
			return false;
		}
	}
	else 
	{
		auto ptr = BearEncoding::ToUTF8((const bcharu8*)buffer.begin(), (const bcharu8*)buffer.end());
		m_doc->Parse((char*)*ptr, 0, TIXML_ENCODING_UTF8);
		if (m_doc->Error())
		{
#ifdef UNICODE
			value_error.assign(*BearEncoding::ToUTF16(m_doc->Value()));
			out_error.assign(*BearEncoding::ToUTF16(m_doc->ErrorDesc()));
#else
			value_error.assign(m_doc->Value());
			out_error.assign(m_doc->ErrorDesc());
#endif
			clear();
			return false;
		}
	}
	return true;
}


void BearXML::clear()
{
	TiXmlDocument*m_doc = static_cast<TiXmlDocument*>(m_Doc);
	if (m_doc)
	{
		m_doc->Clear();
		bear_delete(m_doc);
	}
}

BearString BearXML::get(BearXmlNode node, const  bchar* default_str_val)
{
	if (!m_Doc)
		return (default_str_val);
	if(((TiXmlElement*)node)->GetText()[0])
#ifdef UNICODE
		return *BearEncoding::ToUTF16(((TiXmlElement*)node)->GetText());
#else
	return ((TiXmlElement*)node)->GetText();
#endif
	else return (default_str_val);
}

BearString BearCore::BearXML::getAtribute(BearXmlNode node, const  char* Atribute, const  bchar* default_str_val)
{
	if (!m_Doc)
		return (default_str_val);

	if  (((TiXmlElement*)node)->Attribute(Atribute)!=NULL)
		if (((TiXmlElement*)node)->Attribute(Atribute)[0])
#ifdef UNICODE
			return *BearEncoding::ToUTF16(((TiXmlElement*)node)->Attribute(Atribute));
#else
			return ((TiXmlElement*)node)->Attribute(Atribute);
#endif
		else return (default_str_val);
	else return (default_str_val);
}
BearXML::BearXmlNode BearXML::getNode(const char * name)
{
	if (!m_Doc)
		return NULL;
	TiXmlDocument*m_doc = static_cast<TiXmlDocument*>(m_Doc);
	return m_doc->FirstChildElement(name);
}

BearXML::BearXmlNode BearXML::getNode(BearXmlNode node, const char * name)
{
	if (!m_Doc)
		return NULL;
	return ((TiXmlElement*)node)->FirstChildElement(name);
}

BearXML::BearXmlNode BearCore::BearXML::nextNode(BearXmlNode node, const char * name)
{
	if (!m_Doc)
		return NULL;
	return ((TiXmlElement*)node)->NextSiblingElement(name);
}
