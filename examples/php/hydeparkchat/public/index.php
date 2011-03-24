<? session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
  <head>
    <script src="/javascripts/prototype.js" type="text/javascript"></script>    
    <script src="/javascripts/fdajax.js" type="text/javascript"></script>    
    <style type="text/css">
	  		 #chat { margin: 2em; }
			 #chat_output { overflow: auto; width: 50em; height: 25em; border: 1px solid #999; margin: 1em 0 1em 0; padding-left: 0px;}
			 #chat input#message { list-style: none; width: 45em; margin: 0px; }
			 .chat_message { list-style: none; clear: both; padding: 1px; margin: 1px; background-color: #f5f5f5; }
			 .chat_message span { float: left; width: 8em; text-align: right; margin-right: 0.5em; }
    </style>
    <script type="text/javascript">
	    fdajax.send_mes = function(nn, mes) {
		   if (mes.strip() == "") { return false; }
		   if (nn.strip() == "") { alert("Please enter your nickname."); return false; }
		   new Ajax.Request(fdajax.server_url + "live.fdajax", {
                          onComplete: function(resp) {},
                          method: 'get',
                          parameters: 'cmd=chat_sig' +
                                      '&types='   + "gchat" +
                                      '&mes='     + encodeURIComponent("\""+ nn + "\",\"" + mes + "\"") });
  		   Field.clear('message');
		   Field.focus('message');
		   return false;
		};
		fdajax.grp_peer_call = function(peer_id, ev, nn, mes) {
		    if (ev != "gchat") { return; }
			var s = "<li class=\"chat_message\"><span>" + nn.escapeHTML() + ":</span>" + mes.escapeHTML() + "</li>";
			new Insertion.Bottom("chat_output", s);
			$('chat_output').scrollTop = $('chat_output').scrollHeight;
		};
	 </script>
   </head>
<body>

<div id="chat">
  <h1>Hyde Park Chat FdAjax example</h1>
  <form action="" onsubmit="return fdajax.send_mes(this.nickname.value, this.message.value);">

    My nickname: <input type="text" id="nickname" name="nickname" />
    <ul id="chat_output">
    </ul>
    <input type="text" id="message" name="message" />
    <input type="submit" value="Send" />
  </form>
</div>

<a href="/live.fdajax?cmd=info" target="_blank">FdAjax Module Status</a>

<script type="text/javascript">
  fdajax.waitForEvent(0,'gchat', 0, 0);
</script>

</body>
</html>
