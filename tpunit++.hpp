/**
 * Copyright (c) 2011 Trevor Pounds
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __TPUNITPP_HPP__
#define __TPUNITPP_HPP__

/**
 * Declare printf dependency inline to workaround
 * potential #include <stdio.h> compiler/linker bugs.
 */
extern "C" int printf(const char*, ...);

#define TPUNITPP_VERSION 1000000
#define TPUNITPP_VERSION_MAJOR 1
#define TPUNITPP_VERSION_MINOR 0
#define TPUNITPP_VERSION_PATCH 0

#define ABORT() __fail(__FILE__, __LINE__); return;
#define FAIL()  __fail(__FILE__, __LINE__);
#define PASS()  __pass(__FILE__, __LINE__);

#define ASSERT_TRUE(condition) if(condition) { PASS(); } else { ABORT(); }
#define EXPECT_TRUE(condition) if(condition) { PASS(); } else { FAIL(); }
#define ASSERT_FALSE(condition) if(condition) { ABORT(); } else { PASS(); }
#define EXPECT_FALSE(condition) if(condition) { FAIL(); } else { PASS(); }
#define ASSERT_EQUAL(lhs, rhs) if(lhs == rhs) { PASS(); } else { ABORT(); }
#define EXPECT_EQUAL(lhs, rhs) if(lhs == rhs) { PASS(); } else { FAIL(); }
#define ASSERT_NOT_EQUAL(lhs, rhs) if(lhs != rhs) { PASS(); } else { ABORT(); }
#define EXPECT_NOT_EQUAL(lhs, rhs) if(lhs != rhs) { PASS(); } else { FAIL(); }
#define ASSERT_GREATER_THAN(lhs, rhs) if(lhs > rhs) { PASS(); } else { ABORT(); }
#define EXPECT_GREATER_THAN(lhs, rhs) if(lhs > rhs) { PASS(); } else { FAIL(); }
#define ASSERT_GREATER_THAN_EQUAL(lhs, rhs) if(lhs >= rhs) { PASS(); } else { ABORT(); }
#define EXPECT_GREATER_THAN_EQUAL(lhs, rhs) if(lhs >= rhs) { PASS(); } else { FAIL(); }
#define ASSERT_LESS_THAN(lhs, rhs) if(lhs < rhs) { PASS(); } else { ABORT(); }
#define EXPECT_LESS_THAN(lhs, rhs) if(lhs < rhs) { PASS(); } else { FAIL(); }
#define ASSERT_LESS_THAN_EQUAL(lhs, rhs) if(lhs <= rhs) { PASS(); } else { ABORT(); }
#define EXPECT_LESS_THAN_EQUAL(lhs, rhs) if(lhs <= rhs) { PASS(); } else { FAIL(); }
// TODO: floating point/range macros (e.g. google test)

#define ASSERT_THROW(statement, exception) try { statement; ABORT(); } catch(const exception& e) { PASS(); } catch(...) { ABORT(); }
#define EXPECT_THROW(statement, exception) try { statement; FAIL(); } catch(const exception& e) { PASS(); } catch(...) { FAIL(); }
#define ASSERT_NO_THROW(statement) try { statement; PASS(); } catch(...) { ABORT(); }
#define EXPECT_NO_THROW(statement) try { statement; PASS(); } catch(...) { FAIL(); }
#define ASSERT_ANY_THROW(statement) try { statement; ABORT(); } catch(...) { PASS(); }
#define EXPECT_ANY_THROW(statement) try { statement; FAIL(); } catch(...) { PASS(); }

#define AFTER(M)        After(&M, "After: " #M)
#define AFTER_CLASS(M)  AfterClass(&M, "AfterClass: " #M)
#define BEFORE(M)       Before(&M, "Before: " #M)
#define BEFORE_CLASS(M) BeforeClass(&M, "BeforeClass: " #M)
#define TEST(M)         Test(&M, #M)

namespace tpunit
{
   /**
    * The primary class that provides the integration point for creating user
    * defined test cases. To get started one only needs to derive from TestFixture,
    * define a few test methods and register them with the base constructor.
    */
   class TestFixture
   {
      private:

         /**
          * A generic class representing a TestFixture method.
          */
         struct method
         {
            method(TestFixture* obj, void (TestFixture::*addr)(), const char* name, unsigned char type)
               : _this(obj)
               , _addr(addr)
               , _type(type)
               , _next(0)
            {
               char* dest = _name;
               while(name && *name != 0)
                  { *dest++ = *name++; }
               dest = 0;
            }

            TestFixture* _this;
            void (TestFixture::*_addr)();
            char _name[256];

            enum
            {
               AFTER_METHOD,  AFTER_CLASS_METHOD,
               BEFORE_METHOD, BEFORE_CLASS_METHOD,
               TEST_METHOD
            };
            unsigned char _type;

            method* _next;
         };

         /**
          * A generic class representing a TestFixture.
          */
         struct fixture
         {
            fixture()
               : _afters(0),  _after_classes(0) 
               , _befores(0), _before_classes(0) 
               , _tests(0),   _next(0)
               {}

            method* _afters;
            method* _after_classes;
            method* _befores;
            method* _before_classes;
            method* _tests;

            fixture* _next;
         };

      public:

         /**
          * The base constructor of all test fixtures used to register methods executed by the default runner.
          *
          * @param[in] m0...m29 A list of methods to register with the test fixture.
          */
         TestFixture(method* m0,      method* m1  = 0, method* m2  = 0, method* m3  = 0, method* m4  = 0,
                     method* m5  = 0, method* m6  = 0, method* m7  = 0, method* m8  = 0, method* m9  = 0,
                     method* m10 = 0, method* m11 = 0, method* m12 = 0, method* m13 = 0, method* m14 = 0,
                     method* m15 = 0, method* m16 = 0, method* m17 = 0, method* m18 = 0, method* m19 = 0,
                     method* m20 = 0, method* m21 = 0, method* m22 = 0, method* m23 = 0, method* m24 = 0,
                     method* m25 = 0, method* m26 = 0, method* m27 = 0, method* m28 = 0, method* m29 = 0)
         {
            fixture* f = __fixtures();
            while(f && f->_next) { f = f->_next; }
            f = (f) ? f->_next = new fixture : __fixtures() = new fixture;

            #define SET_FIXTURE_METHOD(M) \
               if(M) \
               { \
                  method** m = 0; \
                  switch(M->_type) \
                  { \
                     case method::AFTER_METHOD:        m = &f->_afters;         break; \
                     case method::AFTER_CLASS_METHOD:  m = &f->_after_classes;  break; \
                     case method::BEFORE_METHOD:       m = &f->_befores;        break; \
                     case method::BEFORE_CLASS_METHOD: m = &f->_before_classes; break; \
                     case method::TEST_METHOD:         m = &f->_tests;          break; \
                  } \
                  while(*m && (*m)->_next) { m = &(*m)->_next; } \
                  (*m) ? (*m)->_next = M : *m = M; \
               }
            SET_FIXTURE_METHOD(m0)  SET_FIXTURE_METHOD(m1)  SET_FIXTURE_METHOD(m2)  SET_FIXTURE_METHOD(m3)
            SET_FIXTURE_METHOD(m4)  SET_FIXTURE_METHOD(m5)  SET_FIXTURE_METHOD(m6)  SET_FIXTURE_METHOD(m7)
            SET_FIXTURE_METHOD(m8)  SET_FIXTURE_METHOD(m9)  SET_FIXTURE_METHOD(m10) SET_FIXTURE_METHOD(m11)
            SET_FIXTURE_METHOD(m12) SET_FIXTURE_METHOD(m13) SET_FIXTURE_METHOD(m14) SET_FIXTURE_METHOD(m15)
            SET_FIXTURE_METHOD(m16) SET_FIXTURE_METHOD(m17) SET_FIXTURE_METHOD(m18) SET_FIXTURE_METHOD(m19)
            SET_FIXTURE_METHOD(m20) SET_FIXTURE_METHOD(m21) SET_FIXTURE_METHOD(m22) SET_FIXTURE_METHOD(m23)
            SET_FIXTURE_METHOD(m24) SET_FIXTURE_METHOD(m25) SET_FIXTURE_METHOD(m26) SET_FIXTURE_METHOD(m27)
            SET_FIXTURE_METHOD(m28) SET_FIXTURE_METHOD(m29)
            #undef SET_FIXTURE_METHOD
         }

         ~TestFixture()
         {
            __delete_fixtures(__fixtures());
            __fixtures() = 0;
         }

         /**
          * Registers a method to run once immediately after each test method registered with the test fixture.
          *
          * @param[in] _method A method to register with the test fixture.
          * @param[in] _name The internal name of the method used when status messages are displayed.
          */
         template <typename C>
         method* After(void (C::*_method)(), const char* _name)
            { return new method(this, reinterpret_cast<void (TestFixture::*)()>(_method), _name, method::AFTER_METHOD); }

         /**
          * Registers a method to run once immediately after all after/before/test methods registered with
          * the test fixture. Useful for cleaning up shared state used by methods in a test fixture.
          *
          * @param[in] _method A method to register with the test fixture.
          * @param[in] _name The internal name of the method used when status messages are displayed.
          */
         template <typename C>
         method* AfterClass(void (C::*_method)(), const char* _name)
            { return new method(this, reinterpret_cast<void (TestFixture::*)()>(_method), _name, method::AFTER_CLASS_METHOD); }

         /**
          * Registers a method to run once immediately before each test method registered with the test fixture.
          *
          * @param[in] _method A method to register with the test fixture.
          * @param[in] _name The internal name of the method used when status messages are displayed.
          */
         template <typename C>
         method* Before(void (C::*_method)(), const char* _name)
            { return new method(this, reinterpret_cast<void (TestFixture::*)()>(_method), _name, method::BEFORE_METHOD); }

         /**
          * Registers a method to run once immediately before all after/before/test methods registered with
          * the test fixture. Useful for intializing shared state used by methods in a test fixture.
          *
          * @param[in] _method A method to register with the test fixture.
          * @param[in] _name The internal name of the method used when status messages are displayed.
          */
         template <typename C>
         method* BeforeClass(void (C::*_method)(), const char* _name)
            { return new method(this, reinterpret_cast<void (TestFixture::*)()>(_method), _name, method::BEFORE_CLASS_METHOD); }

         /**
          * Registers a method to run as a test with the test fixture.
          *
          * @param[in] _method A method to register with the test fixture.
          * @param[in] _name The internal name of the method used when status messages are displayed.
          */
         template <typename C>
         method* Test(void (C::*_method)(), const char* _name)
            { return new method(this, reinterpret_cast<void (TestFixture::*)()>(_method), _name, method::TEST_METHOD); }

      protected:

         static int __do_run()
         {
            fixture* f = __fixtures();
            while(f)
            {
               __do_methods(f->_before_classes);
               __do_tests(f);
               __do_methods(f->_after_classes);
               f = f->_next;
            }
            return __fails();
         }
    
         static void __fail(const char* _file, int _line)
         {
            printf("[        FAIL ]    @ %s:%i\n", _file, _line);
            __fails()++;
         }

         static void __pass(const char* _file, int _line)
         {
      //      if(is_verbose())
      //         { printf("[        PASS ]    @ %s:%i\n", _file, _line); }
         }

      private:

         void __delete_methods(method* m)
         {
            while(m)
            {
               method* mnext = m->_next;
               delete m;
               m = mnext;
            }
         }

         void __delete_fixtures(fixture* f)
         {
            while(f)
            {
               __delete_methods(f->_afters);
               __delete_methods(f->_after_classes);
               __delete_methods(f->_befores);
               __delete_methods(f->_before_classes);
               __delete_methods(f->_tests);
               fixture* fnext = f->_next;
               delete f;
               f = fnext;
            }
         }

         static void __do_methods(method* m)
         {
            while(m)
            {
               (*m->_this.*m->_addr)();
               m = m->_next;
            }
         }

         static void __do_tests(fixture* f)
         {
            method* t = f->_tests;
            while(t)
            {
               __do_methods(f->_befores);

               int _prev_fails = __fails();
               printf("[ RUN         ] %s\n", t->_name);
               (*t->_this.*t->_addr)();
               if(_prev_fails == __fails())
                  { printf("[        PASS ] %s\n", t->_name); }
               t = t->_next;

               __do_methods(f->_afters);
            }
         }

         static int& __fails()
         {
            static int _fails = 0;
            return _fails;
         }

         static fixture*& __fixtures()
         {
            static fixture* _fixtures = 0;
            return _fixtures;
         }
   };

   /**
    * A class containing the primary entry point for running all registered
    * tpunit++ test cases. Generally this class is wrapped by the user's
    * \em main function.
    */
   class Tests : TestFixture
   {
      public:

         /**
          * Run all of the registered test cases and return the number of failed assertions.
          *
          * @return The number of failing assertions. (e.g. zero if all tests pass, otherwise non-zero)
          */
         static int Run() { return TestFixture::__do_run(); }

      private:

         Tests() : TestFixture(0) { /* disable instance creation */ }
   };
} // namespace tpunit
#endif //__TPUNITPP_HPP__
