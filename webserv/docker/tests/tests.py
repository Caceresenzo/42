import unittest
import os

import requests

BASE_URL = "http://127.0.0.1:80"


def _make_url(url):
	if url.startswith("http"):
		return url
	
	return BASE_URL + url


class WebservTestCase(unittest.TestCase):
	
	def assertGetStatusCode(self, url, status_code, **kwargs):
		response = requests.get(_make_url(url), **kwargs)
		
		self.assertTrue(response.status_code == status_code, "GET {} expected {} but got {}".format(url, status_code, response.status_code))

	def assertGet(self, url, content, **kwargs):
		response = requests.get(_make_url(url), **kwargs)
		
		self.assertTrue(response.text == content, "GET {} expected {} but got {}".format(url, content, response.text))

	def assertPostStatusCode(self, url, status_code, body, **kwargs):
		response = requests.post(_make_url(url), data=body, **kwargs)
		
		self.assertTrue(response.status_code == status_code, "POST {} expected {} but got {}".format(url, status_code, response.status_code))
	
	def assertDeleteStatusCode(self, url, status_code, **kwargs):
		response = requests.delete(_make_url(url), **kwargs)
		
		self.assertTrue(response.status_code == status_code, "DELETE {} expected {} but got {}".format(url, status_code, response.status_code))
		
	def assertPutStatusCode(self, url, status_code, body, **kwargs):
		response = requests.put(_make_url(url), data=body, **kwargs)
		
		self.assertTrue(response.status_code == status_code, "PUT {} expected {} but got {}".format(url, status_code, response.status_code))

	def assertOptionStatusCode(self, url, status_code, **kwargs):
		response = requests.options(_make_url(url), **kwargs)
		
		self.assertTrue(response.status_code == status_code, "OPTIONS {} expected {} but got {}".format(url, status_code, response.status_code))

	def assertHeadStatusCode(self, url, status_code, **kwargs):
		response = requests.head(_make_url(url), **kwargs)
		
		self.assertTrue(response.status_code == status_code, "HEAD {} expected {} but got {}".format(url, status_code, response.status_code))


class TestGetMethod(WebservTestCase):
	
	def test_simple(self):
		self.assertGetStatusCode("/", 200)

	def test_not_found(self):
		self.assertGetStatusCode("/hello", 404)

	def test_no_listing(self):
		self.assertGetStatusCode("/no-listing", 404)


class TestPostMethod(WebservTestCase):
	
	def test_simple(self):
		self.assertPostStatusCode("/test__simple_file_post.txt", 201, "Hello World".encode("ascii"))
		self.assertGet("/test__simple_file_post.txt", "Hello World")
	
	def test_double(self):
		self.assertPostStatusCode("/test__simple_file_post_2.txt", 201, "Hello".encode("ascii"))
		self.assertPostStatusCode("/test__simple_file_post_2.txt", 200, "World".encode("ascii"))
		self.assertGet("/test__simple_file_post_2.txt", "HelloWorld")

	def test_not_allowed(self):
		self.assertPostStatusCode("/_tests/x.sh", 405, "Hello".encode("ascii"))


class TestPutMethod(WebservTestCase):

	def test_simple(self):
		self.assertPutStatusCode("/test__simple_file_put.txt", 201, "Filed changed".encode("ascii"))
		self.assertGet("/test__simple_file_put.txt", "Filed changed")
	
	def test_double(self):
		self.assertPutStatusCode("/test__simple_file_put_2.txt", 201, "Filed changed".encode("ascii"))
		self.assertPutStatusCode("/test__simple_file_put_2.txt", 200, "Filed changed 2 times".encode("ascii"))
		self.assertGet("/test__simple_file_put_2.txt", "Filed changed 2 times")


class TestDeleteMethod(WebservTestCase):
	
	def test_simple(self):
		self.assertPostStatusCode("/test__will_be_deleted.txt", 201, "Hello World".encode("ascii"))
		self.assertDeleteStatusCode("/test__will_be_deleted.txt", 200)
	
	def test_not_found(self):
		self.assertDeleteStatusCode("/test__cannot_be_deleted_because_not_exists.txt", 204)


class TestOptionsMethod(WebservTestCase):
	
	def test_simple(self):
		self.assertOptionStatusCode("/", 200)
		self.assertOptionStatusCode("/_tests", 200)

	def test_wrong_path(self):
		self.assertOptionStatusCode("/wrong_path", 200)


class TestHeadMethod(WebservTestCase):
	
	def test_simple(self):
		self.assertHeadStatusCode("/", 200)
		self.assertHeadStatusCode("/_tests", 200)

	def test_wrong_path(self):
		self.assertHeadStatusCode("/wrong_path", 404)


class TestPathsMethod(WebservTestCase):
	
	def test_directory(self):
		self.assertGetStatusCode("/_tests", 200)
		self.assertGetStatusCode("/_tests/", 200)
	
	def test_sh(self):
		self.assertGetStatusCode("/_tests/x.sh", 200)
	
	def test_py(self):
		self.assertGetStatusCode("/_tests/x.py", 200)
		self.assertGetStatusCode("/_tests/x2.py", 200)
	
	def test_wordpress(self):
		self.assertGetStatusCode("/wordpress/", 200)


class TestMultipleServerMethod(WebservTestCase):
	
	def test_same_port_diff_host(self):
		self.assertGetStatusCode("/", 405, headers={ "host": "second.com" })
		self.assertGetStatusCode("/", 405, headers={ "host": "second2.com" })
		self.assertHeadStatusCode("/", 200, headers={ "host": "second.com" })
		self.assertHeadStatusCode("/", 200, headers={ "host": "second2.com" })
		self.assertGetStatusCode("/", 200, headers={ "host": "i-do-not-exists.com" })
	
	def test_diff_host(self):
		self.assertGetStatusCode("http://127.0.0.1:81", 404, headers={ "host": "second.com" })
		self.assertGetStatusCode("http://127.0.0.1:81", 200, headers={ "host": "third.com" })


if __name__ == '__main__':

	def remove_if_exists(path):
		if os.path.exists(path):
			print("deleting:", path)
			os.remove(path)
	
	remove_if_exists("test__simple_file.txt")
	remove_if_exists("test__simple_file_2.txt")
	remove_if_exists("test__simple_file_post.txt")
	remove_if_exists("test__simple_file_post_2.txt")
	remove_if_exists("test__simple_file_put.txt")
	remove_if_exists("test__simple_file_put_2.txt")
	remove_if_exists("test__will_be_deleted.txt")
	remove_if_exists("test__cannot_be_deleted_because_not_exists.txt")
	
	print("\n\nrunning tests:")
	
	unittest.main()
