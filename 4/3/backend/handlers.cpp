#include "handlers.hpp"

using namespace std;


Response *SignupHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string role = req->getBodyParam("role");
  string city = req->getBodyParam("city");
  string pass = req->getBodyParam("password");
  string s = "POST signup ? username " + username + " role " + role + "password" + pass+"city"+ city;
  line command = split_string(s);
  try { UTKALA->signup(UTKALA->find_part(USERNAME, command) , UTKALA->find_part(PASSWORD, command) , UTKALA->find_part(ROLE, command) , UTKALA->find_part(CITY, command)); }
  catch (string err) { return show_message(err); }
  return show_message(OK);
}


Response *show_message(string msg) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>" + msg + "</h1>";
  body += "</body>";
  body += "</html>";
  body += "<div>";
  body += "<form action='/' method='get'>";
  body += "<button type='submit' >return</button>";
  body += "</form>";
  body += "</div>";
  res->setBody(body);
  return res;
}
