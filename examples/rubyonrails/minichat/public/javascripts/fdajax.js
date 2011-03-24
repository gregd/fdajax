/*  Full-duplex Ajax module for Lighttpd, version 0.8
 *  (c) 2007 Grzegorz Daniluk
/*--------------------------------------------------------------------------*/

var fdajax = {
   server_url: "/live.fdajax",
   run_loop: false,
   user_id: 0,
   win_id: 0,
   ev_types: "",
   cur_req: null,
   from_sec: 0,
   from_usec: 0,
   first: true,

   waitForEvent: function(user_id, ev_types, sec, usec) {
      this.user_id = user_id;
      this.win_id = Math.floor(Math.random() * 2147483646 + 1);
      this.ev_types = ev_types;
      this.from_sec = sec;
      this.from_usec = usec;
      Event.observe(window, "load", fdajax.startloop);
   },
   redirect: function(www_id) {
      fdajax.cancel();
      alert("Do not open a second window or configure www1, www2, etc addresses in your application.");
      window.location = "/minichat/login";
   },
   relogin: function(reason) {
      fdajax.cancel();
      if (reason == "ipaddr") {
         alert("Please log in once again, your IP address has changed.");
      } else if (reason == "sessid") {
         alert("Please log in once again, your session id is incorrect.");
      }
      window.location = "/minichat/login";
   },
   nocookies: function() {
      fdajax.cancel();
   },
   notfound: function() {
      fdajax.cancel();
      alert("You are not logged to FdAjax module.");
      window.location = "/minichat/login";
   },
   cancel: function() {
      fdajax.run_loop = false;
      if (fdajax.cur_req) {
         if (fdajax.cur_req.transport && fdajax.cur_req.transport.readyState > 0) {
            fdajax.cur_req.transport.onreadystatechange = function() {};
            fdajax.cur_req.transport.abort();

            new Ajax.Request(fdajax.server_url, { method: 'get', asynchronous: false,
                             parameters: 'cmd=cancel' + '&user_id=' + fdajax.user_id + '&win_id=' + fdajax.win_id });
         }
         fdajax.cur_req.transport = null;
         fdajax.cur_req = null;
      }
      return false;
   },
   send_request: function() {
      if (!fdajax.run_loop) {
         return;
      }
      var opt = {
         onSuccess: function(resp) {
            fdajax.cur_req = null;
            try { eval(resp.responseText); } catch (e) {}
            if (fdajax.run_loop) {
               setTimeout("fdajax.send_request();", 50);
            }
         },
         onFailure: function(req) {
            fdajax.cur_req = null;
            setTimeout("fdajax.send_request();", 10000);
         },
         method: 'get',
         parameters: "cmd=wait&user_id=" + fdajax.user_id + "&win_id=" + fdajax.win_id + "&types=" + fdajax.ev_types
      };
      if (fdajax.first) {
         fdajax.first = false;
         opt.parameters += "&sec=" + fdajax.from_sec + "&usec=" + fdajax.from_usec;
      }
      fdajax.cur_req = new Ajax.Request(fdajax.server_url, opt);
   },
   startloop: function() {
      fdajax.run_loop = true;
      Event.observe(window, "unload", fdajax.cancel);
      setTimeout("fdajax.send_request();", 1000);
   },
   stoploop: function() {
      if (fdajax.run_loop) {
         fdajax.run_loop = false;
         alert("You have been logged out from FdAjax module.");
         window.location = "/minichat/login";
      }
   },
   maxwin: function() {
      if (fdajax.run_loop) {
         fdajax.run_loop = false;
         alert("Too many open windows. This window has lost the connection to FdAjax module.");
      }
   },
   no_guests: function () {
      alert("Guest users not allowed.");
   },
   peer_call: function(peer_id, ev, ob_id, par1) {
   },
   grp_peer_call: function (peer_id, ev, par1) {
   },
   ping: function() {
      // In case of chunked mode the ping function might be empty
   }
};
