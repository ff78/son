#ifndef _COMMON_H
#define	_COMMON_H

#ifdef YN_WINDOWS
#pragma warning(disable:4251) 
#endif

#include <vector>
#include <map>
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <sstream>
#include <functional>
#ifdef YN_LINUX
#include <pthread.h>
#include <string.h>
#endif
using namespace std;


#define COCOS2D_DEBUG   1


#define ID_GATE_COEFFICIENT         0x1000000000000
#define ID_ENGINE_COEFFICIENT       0x100000000
#define ID_MASK                     0xFFFFFFFF

#define _MAX_MSGSIZE 16 * 1024      // 暂定一个消息最大为16k  
#define BLOCKSECONDS    5          // INIT函数阻塞时间  
#define INBUFSIZE   (64*1024)       //? 具体尺寸根据剖面报告调整  接收数据的缓存  
#define OUTBUFSIZE  (2*1024)        //? 具体尺寸根据剖面报告调整。 发送数据的缓存，当不超过8K时，FLUSH只需要SEND一次  

#define MAX_QUEST_BYTES           400
#if defined(YN_WINDOWS)
#define		tvsnprintf		_vsnprintf
#define		tstricmp		_stricmp
#define		tsnprintf		_snprintf
#elif defined(YN_LINUX)
#define		tvsnprintf		vsnprintf
#define		tstricmp		strcasecmp
#define		tsnprintf		snprintf
#endif

#ifdef YN_WINDOWS

typedef signed  __int8  sint8;
typedef unsigned __int8  uint8;
typedef signed  __int16  sint16;
typedef unsigned __int16  uint16;
typedef signed  __int32  sint32;
typedef __int32          int32;
typedef unsigned __int32  uint32;
typedef signed  __int64  sint64;
typedef unsigned __int64  uint64;

typedef    int   sint;   // at least 32bits (depend of processor)
typedef unsigned int   uint;   // at least 32bits (depend of processor)



#define I64 "I64"
#endif

#ifdef YN_LINUX
#include <sys/types.h>

typedef int8_t  sint8;
typedef u_int8_t uint8;
typedef int16_t  sint16;
typedef u_int16_t uint16;
typedef int32_t  sint32;
typedef u_int32_t uint32;
typedef int32_t int32;
typedef long long int  sint64;
typedef unsigned long long int uint64;

typedef   int   sint;   // at least 32bits (depend of processor)
typedef unsigned int   uint;   // at least 32bits (depend of processor)

#define I64 \
  "ll"

    inline string& trim(string &s)
    { 
      if (s.empty())
        return s;
      s.erase(0,s.find_first_not_of(" \n\r\t"));  
      
      return s.erase(s.find_last_not_of(" \n\r\t")+1);
    }
#endif // YN_LINUX

    
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
///////////////////////////////////////////////////////////////////////
//标准数据类型定义
///////////////////////////////////////////////////////////////////////
#define VOID			void			//标准空
typedef unsigned char	UCHAR;			//标准无符号CHAR
typedef char			CHAR;			//标准CHAR
typedef unsigned int	UINT;			//标准无符号INT
typedef int				INT;			//标准INT
typedef unsigned short	USHORT;			//标准无符号short
typedef short			SHORT;			//标准short
typedef unsigned long	ULONG;			//标准无符号LONG(不推荐使用)
typedef long			LONG;			//标准LONG(不推荐使用)
typedef float			FLOAT;			//标准float

typedef UCHAR			uchar;
typedef USHORT			ushort;
typedef UINT			uint;
typedef ULONG			ulong;
typedef ULONG			IP_t;
typedef USHORT			PacketID_t;
typedef INT				BOOL;
typedef UCHAR			BYTE;

typedef SHORT	ID_t;
typedef USHORT	SMUID_t;
typedef	ULONG	SM_KEY;
typedef UINT	ObjID_t;			//场景中固定的所有OBJ拥有不同的ObjID_t
typedef ID_t			SceneID_t;			//场景ID
typedef ID_t			SkillID_t;			//技能
typedef ID_t            BuffID_t;           //Buff
typedef ID_t			ActionID_t;			//动作的ID
typedef ID_t			ImpactID_t;			//效果ID
typedef ID_t			ImpactClassID_t;	//效果分组ID


typedef UINT			GUID_t;	//32位唯一编号。


//用来定义在世界的浮点位置
struct WORLD_POS
{

	FLOAT	 m_fX ;
	FLOAT	 m_fZ ;

	WORLD_POS(VOID)					: m_fX(0.0f), m_fZ(0.0f)	{}
	WORLD_POS(FLOAT fX, FLOAT fZ)	: m_fX(fX)	, m_fZ(fZ)		{}
	VOID	CleanUp( ){
		m_fX = 0.0f ;
		m_fZ = 0.0f ;
	};
	WORLD_POS& operator=(WORLD_POS const& rhs)
	{
		m_fX = rhs.m_fX;
		m_fZ = rhs.m_fZ;
		return *this;
	}
	BOOL	operator==(WORLD_POS& Ref)
	{
		return (fabs(m_fX-Ref.m_fX)+fabs(m_fZ-Ref.m_fZ))<0.0001f;

	}
	BOOL	operator==(const WORLD_POS& Ref)
	{
		return (fabs(m_fX-Ref.m_fX)+fabs(m_fZ-Ref.m_fZ))<0.0001f;

	}
};

	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Math
	*  @{
	*/
	/** Standard 2-dimensional vector.
        @remarks
            A direction in 2D space represented as distances along the 2
            orthogonal axes (x, y). Note that positions, directions and
            scaling factors can be represented by a vector, depending on how
            you interpret the values.
    */

enum char_type {
	char_type_none = 0,
	char_type_player,
	char_type_monster,
	char_type_pet
};

namespace Game_Logic
{
  class map_mutex
  {
  public:
#ifdef YN_LINUX     	
    map_mutex(pthread_mutex_t* mutex)
    {
     mutex_ = mutex;
      pthread_mutex_lock(mutex_);
    }
    ~map_mutex()
    {
      pthread_mutex_unlock(mutex_);
    }
  private:
    pthread_mutex_t * mutex_;
#endif    
  };	
struct player_pos
{
	player_pos(void):scene_id(0),x(0),y(0) {}
	~player_pos(void) {}
	
	int scene_id;
	int x;
	int y;
};
class Vector2
{
public:
    float x, y;

public:
	inline Vector2(): x(0), y(0)
    {
    }

	inline void clear()
	{
		x = 0; y = 0;
	}

    inline Vector2(const float fX, const float fY )
        : x( fX ), y( fY )
    {
    }

    inline explicit Vector2( const float scaler )
        : x( scaler), y( scaler )
    {
    }

    inline explicit Vector2( const float afCoordinate[2] )
        : x( afCoordinate[0] ),
          y( afCoordinate[1] )
    {
    }

    inline explicit Vector2( const int afCoordinate[2] )
    {
        x = (float)afCoordinate[0];
        y = (float)afCoordinate[1];
    }

    inline explicit Vector2( float* const r )
        : x( r[0] ), y( r[1] )
    {
    }

	/** Exchange the contents of this vector with another. 
	*/
	inline void swap(Vector2& other)
	{
		std::swap(x, other.x);
		std::swap(y, other.y);
	}

	inline float operator [] ( const size_t i ) const
    {
         return *(&x+i);
    }

	inline float& operator [] ( const size_t i )
    {
  
        return *(&x+i);
    }

	/// Pointer accessor for direct copying
	inline float* ptr()
	{
		return &x;
	}
	/// Pointer accessor for direct copying
	inline const float* ptr() const
	{
		return &x;
	}

    /** Assigns the value of the other vector.
        @param
            rkVector The other vector
    */
    inline Vector2& operator = ( const Vector2& rkVector )
    {
        x = rkVector.x;
        y = rkVector.y;

        return *this;
    }

	inline Vector2& operator = ( const float fScalar)
	{
		x = fScalar;
		y = fScalar;

		return *this;
	}

    inline bool operator == ( const Vector2& rkVector ) const
    {
        return ( x == rkVector.x && y == rkVector.y );
    }

    inline bool operator != ( const Vector2& rkVector ) const
    {
        return ( x != rkVector.x || y != rkVector.y  );
    }

    // arithmetic operations
    inline Vector2 operator + ( const Vector2& rkVector ) const
    {
        return Vector2(
            x + rkVector.x,
            y + rkVector.y);
    }

    inline Vector2 operator - ( const Vector2& rkVector ) const
    {
        return Vector2(
            x - rkVector.x,
            y - rkVector.y);
    }

    inline Vector2 operator * ( const float fScalar ) const
    {
        return Vector2(
            x * fScalar,
            y * fScalar);
    }

    inline Vector2 operator * ( const Vector2& rhs) const
    {
        return Vector2(
            x * rhs.x,
            y * rhs.y);
    }

    inline Vector2 operator / ( const float fScalar ) const
    {
        if( fScalar == 0.0 )
			return Vector2( 0.f,0.f);

        float fInv = 1.0f / fScalar;

        return Vector2(
            x * fInv,
            y * fInv);
    }

    inline Vector2 operator / ( const Vector2& rhs) const
    {
        return Vector2(
            x / rhs.x,
            y / rhs.y);
    }

    inline const Vector2& operator + () const
    {
        return *this;
    }

    inline Vector2 operator - () const
    {
        return Vector2(-x, -y);
    }

    // overloaded operators to help Vector2
    inline friend Vector2 operator * ( const float fScalar, const Vector2& rkVector )
    {
        return Vector2(
            fScalar * rkVector.x,
            fScalar * rkVector.y);
    }

    inline friend Vector2 operator / ( const float fScalar, const Vector2& rkVector )
    {
        return Vector2(
            fScalar / rkVector.x,
            fScalar / rkVector.y);
    }

    inline friend Vector2 operator + (const Vector2& lhs, const float rhs)
    {
        return Vector2(
            lhs.x + rhs,
            lhs.y + rhs);
    }

    inline friend Vector2 operator + (const float lhs, const Vector2& rhs)
    {
        return Vector2(
            lhs + rhs.x,
            lhs + rhs.y);
    }

    inline friend Vector2 operator - (const Vector2& lhs, const float rhs)
    {
        return Vector2(
            lhs.x - rhs,
            lhs.y - rhs);
    }

    inline friend Vector2 operator - (const float lhs, const Vector2& rhs)
    {
        return Vector2(
            lhs - rhs.x,
            lhs - rhs.y);
    }
    // arithmetic updates
    inline Vector2& operator += ( const Vector2& rkVector )
    {
        x += rkVector.x;
        y += rkVector.y;

        return *this;
    }

    inline Vector2& operator += ( const float fScaler )
    {
        x += fScaler;
        y += fScaler;

        return *this;
    }

    inline Vector2& operator -= ( const Vector2& rkVector )
    {
        x -= rkVector.x;
        y -= rkVector.y;

        return *this;
    }

    inline Vector2& operator -= ( const float fScaler )
    {
        x -= fScaler;
        y -= fScaler;

        return *this;
    }

    inline Vector2& operator *= ( const float fScalar )
    {
        x *= fScalar;
        y *= fScalar;

        return *this;
    }

    inline Vector2& operator *= ( const Vector2& rkVector )
    {
        x *= rkVector.x;
        y *= rkVector.y;

        return *this;
    }

    inline Vector2& operator /= ( const float fScalar )
    {
         if( fScalar == 0.0 )
			return *this;

        float fInv = 1.0f / fScalar;

        x *= fInv;
        y *= fInv;

        return *this;
    }

    inline Vector2& operator /= ( const Vector2& rkVector )
    {
        x /= rkVector.x;
        y /= rkVector.y;

        return *this;
    }

    /** Returns the length (magnitude) of the vector.
        @warning
            This operation requires a square root and is expensive in
            terms of CPU operations. If you don't need to know the exact
            length (e.g. for just comparing lengths) use squaredLength()
            instead.
    */
    inline float length () const
    {
        return sqrt( x * x + y * y );
    }

    /** Returns the square of the length(magnitude) of the vector.
        @remarks
            This  method is for efficiency - calculating the actual
            length of a vector requires a square root, which is expensive
            in terms of the operations required. This method returns the
            square of the length of the vector, i.e. the same as the
            length but before the square root is taken. Use this if you
            want to find the longest / shortest vector without incurring
            the square root.
    */
    inline float squaredLength () const
    {
        return x * x + y * y;
    }
    /** Returns the distance to another vector.
        @warning
            This operation requires a square root and is expensive in
            terms of CPU operations. If you don't need to know the exact
            distance (e.g. for just comparing distances) use squaredDistance()
            instead.
    */
    inline float distance(const Vector2& rhs) const
    {
        return (*this - rhs).length();
    }

    /** Returns the square of the distance to another vector.
        @remarks
            This method is for efficiency - calculating the actual
            distance to another vector requires a square root, which is
            expensive in terms of the operations required. This method
            returns the square of the distance to another vector, i.e.
            the same as the distance but before the square root is taken.
            Use this if you want to find the longest / shortest distance
            without incurring the square root.
    */
    inline float squaredDistance(const Vector2& rhs) const
    {
        return (*this - rhs).squaredLength();
    }

    /** Calculates the dot (scalar) product of this vector with another.
        @remarks
            The dot product can be used to calculate the angle between 2
            vectors. If both are unit vectors, the dot product is the
            cosine of the angle; otherwise the dot product must be
            divided by the product of the lengths of both vectors to get
            the cosine of the angle. This result can further be used to
            calculate the distance of a point from a plane.
        @param
            vec Vector with which to calculate the dot product (together
            with this one).
        @returns
            A float representing the dot product value.
    */
    inline float dotProduct(const Vector2& vec) const
    {
        return x * vec.x + y * vec.y;
    }

    /** Normalises the vector.
        @remarks
            This method normalises the vector such that it's
            length / magnitude is 1. The result is called a unit vector.
        @note
            This function will not crash for zero-sized vectors, but there
            will be no changes made to their components.
        @returns The previous length of the vector.
    */
    inline float normalise()
    {
        float fLength = sqrt( x * x + y * y);

        // Will also work for zero-sized vectors, but will change nothing
        if ( fLength > 1e-08 )
        {
            float fInvLength = 1.0f / fLength;
            x *= fInvLength;
            y *= fInvLength;
        }

        return fLength;
    }



    /** Returns a vector at a point half way between this and the passed
        in vector.
    */
    inline Vector2 midPoint( const Vector2& vec ) const
    {
        return Vector2(
            ( x + vec.x ) * 0.5f,
            ( y + vec.y ) * 0.5f );
    }

    /** Returns true if the vector's scalar components are all greater
        that the ones of the vector it is compared against.
    */
    inline bool operator < ( const Vector2& rhs ) const
    {
        if( x < rhs.x && y < rhs.y )
            return true;
        return false;
    }

    /** Returns true if the vector's scalar components are all smaller
        that the ones of the vector it is compared against.
    */
    inline bool operator > ( const Vector2& rhs ) const
    {
        if( x > rhs.x && y > rhs.y )
            return true;
        return false;
    }

    /** Sets this vector's components to the minimum of its own and the
        ones of the passed in vector.
        @remarks
            'Minimum' in this case means the combination of the lowest
            value of x, y and z from both vectors. Lowest is taken just
            numerically, not magnitude, so -1 < 0.
    */
    inline void makeFloor( const Vector2& cmp )
    {
        if( cmp.x < x ) x = cmp.x;
        if( cmp.y < y ) y = cmp.y;
    }

    /** Sets this vector's components to the maximum of its own and the
        ones of the passed in vector.
        @remarks
            'Maximum' in this case means the combination of the highest
            value of x, y and z from both vectors. Highest is taken just
            numerically, not magnitude, so 1 > -3.
    */
    inline void makeCeil( const Vector2& cmp )
    {
        if( cmp.x > x ) x = cmp.x;
        if( cmp.y > y ) y = cmp.y;
    }

    /** Generates a vector perpendicular to this vector (eg an 'up' vector).
        @remarks
            This method will return a vector which is perpendicular to this
            vector. There are an infinite number of possibilities but this
            method will guarantee to generate one of them. If you need more
            control you should use the Quaternion class.
    */
    inline Vector2 perpendicular(void) const
    {
        return Vector2 (-y, x);
    }
    /** Calculates the 2 dimensional cross-product of 2 vectors, which results
		in a single floating point value which is 2 times the area of the triangle.
    */
    inline float crossProduct( const Vector2& rkVector ) const
    {
        return x * rkVector.y - y * rkVector.x;
    }
    /** Generates a new random vector which deviates from this vector by a
        given angle in a random direction.
        @remarks
            This method assumes that the random number generator has already
            been seeded appropriately.
        @param
            angle The angle at which to deviate in radians
        @param
            up Any vector perpendicular to this one (which could generated
            by cross-product of this vector and any other non-colinear
            vector). If you choose not to provide this the function will
            derive one on it's own, however if you provide one yourself the
            function will be faster (this allows you to reuse up vectors if
            you call this method more than once)
        @returns
            A random vector which deviates from this vector by angle. This
            vector will not be normalised, normalise it if you wish
            afterwards.
    */

    /** Returns true if this vector is zero length. */
    inline bool isZeroLength(void) const
    {
        float sqlen = (x * x) + (y * y);
        return (sqlen < (1e-06 * 1e-06));

    }

    /** As normalise, except that this vector is unaffected and the
        normalised vector is returned as a copy. */
    inline Vector2 normalisedCopy(void) const
    {
        Vector2 ret = *this;
        ret.normalise();
        return ret;
    }

    /** Calculates a reflection vector to the plane with the given normal .
    @remarks NB assumes 'this' is pointing AWAY FROM the plane, invert if it is not.
    */
    inline Vector2 reflect(const Vector2& normal) const
    {
        return Vector2( *this - ( 2 * this->dotProduct(normal) * normal ) );
    }

    // special points
    static const Vector2 ZERO;
    static const Vector2 UNIT_X;
    static const Vector2 UNIT_Y;
    static const Vector2 NEGATIVE_UNIT_X;
    static const Vector2 NEGATIVE_UNIT_Y;
    static const Vector2 UNIT_SCALE;

    /** Function for writing to a stream.
    */
    inline friend std::ostream& operator <<
        ( std::ostream& o, const Vector2& v )
    {
        o << "Vector2(" << v.x << ", " << v.y <<  ")";
        return o;
    }

};
    class polygon
    {
    public:
        inline polygon() {}
        inline ~polygon() {}
        inline void build_edges()
        {
            Vector2 p1;
            Vector2 p2;
            edges_.clear();
            
            for( uint i = 0; i < points_.size(); i++ )
            {
                p1 = points_[i];
                if( i + 1 >= points_.size() )
                {
                    p2 = points_[0];
                }
                else
                {
                    p2 = points_[i+1];
                }
                edges_.push_back( p2 - p1 );
            }

        }
        inline void add_edge( Vector2& edge ) { edges_.push_back(edge);}
        inline void add_point( Vector2& point) { points_.push_back( point); }
        inline void get_edges( vector<Vector2>& edges ) { edges = edges_; }
        inline  void get_points( vector<Vector2>& points ) { points = points_; }
        inline Vector2 get_center( void)
        {
            float total_x = 0.f;
            float total_y = 0.f;
            vector<Vector2>::iterator itv;
            for( itv = points_.begin(); itv != points_.end(); ++itv )
            {
                total_x += (*itv).x;
                total_y += (*itv).y;
            }

            return Vector2(total_x/(float)points_.size(), total_y/(float)points_.size());
        }
        inline void offset( Vector2 v )
        {
            offset( v.x, v.y );
        }
        inline void offset( float x, float y )
        {
            vector<Vector2>::iterator itv;
            Vector2 p;
            for( itv = points_.begin(); itv != points_.end(); ++itv )
            {
                p = (*itv);
                (*itv) = Vector2( p.x + x, p.y + y );
            }
        }
        int get_edges_size() {return edges_.size();}
        int get_points_size() {return points_.size();}
        Vector2 get_point_by_index( int idx) 
        {
            if( (uint)idx > points_.size() )
                return Vector2(0,0);
            return points_[idx];

        }
        Vector2 get_edge_by_index( int idx ) 
        {
            if( (uint)idx > edges_.size() )
                return Vector2(0,0);
            return edges_[idx];

        }
    private:
        vector<Vector2> points_;
        vector<Vector2> edges_;

    };

}
#ifdef GAME_CLIENT
#include "cocos/base/CCPlatformMacros.h"
namespace cocos2d
{

class CCFileData
{
public:
    CCFileData(const char* pszFileName, const char* pszMode)
        : m_pBuffer(0)
        , m_uSize(0)
    {
        m_pBuffer = getFileData(pszFileName, pszMode, &m_uSize);
    }
    ~CCFileData()
    {
        CC_SAFE_DELETE_ARRAY(m_pBuffer);
    }

    bool reset(const char* pszFileName, const char* pszMode)
    {
        CC_SAFE_DELETE_ARRAY(m_pBuffer);
        m_uSize = 0;
        m_pBuffer = getFileData(pszFileName, pszMode, &m_uSize);
        return (m_pBuffer) ? true : false;
    }
	static unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
	{
		unsigned char * pBuffer = NULL;

		do 
		{
			// read the file from hardware
			FILE *fp = fopen(pszFileName, pszMode);
			if(!fp)
				break;

			fseek(fp,0,SEEK_END);
			*pSize = ftell(fp);
			fseek(fp,0,SEEK_SET);
			pBuffer = new unsigned char[*pSize];
			*pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
			fclose(fp);
		} while (0);

		if (! pBuffer)
		{
			return NULL;
		}
		return pBuffer;
	}
    CC_SYNTHESIZE_READONLY(unsigned char *, m_pBuffer, Buffer);
    CC_SYNTHESIZE_READONLY(unsigned long ,  m_uSize,   Size);
};
}
#endif

#endif
