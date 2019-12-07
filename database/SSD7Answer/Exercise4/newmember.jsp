<%@ page language="java" import="library.*" errorPage="error.jsp"%>

<!-- Page scoped bean for a common header and footer. -->
<jsp:useBean id="tags" scope="page" class="library.CommonTags" />

<!DOCTYPE html PUBLIC "-//W3C//DTD html 4.0 transitional//EN">
<%
  // Get an error messages in the request object.
  String errMsg = (request.getParameter("errMsg") == null)
                ? ""
                : request.getParameter("errMsg");
  String uname = (request.getParameter("uname") == null)
                ? ""
                : request.getParameter("uname");
%>
<html>
<head>
<meta name="Description"
	content="iCarnegie.Library: a demonstration online database project.">

<title>iCarnegie.Library: a demonstration online database
project.</title>
<link rel="stylesheet" type="text/css" href="styles.css">
</head>

<body>
<!-- Display the common header using a JavaBean, omit the search link. -->
<%=tags.getHeader("OMIT_SEARCH")%>

<form action="servlet/MemberRegisterController" method="post">
<table>
	<tr bgcolor="">
		<td width="20%"></td>
		<td bgcolor="red">Enter Member Details</td>
	</tr>
	<tr>
		<td width="20%"></td>
		<td>
		<table cellpadding="10" cellspacing="3" border="1">
			<tr>
				<td align="left" valign="top">ID:</td>

				<td align="left" valign="top"><input type="text" name="uname"
					maxlength="9" size="20"><br><b class="error"><%=  errMsg%></b></td>
			</tr>

			<tr>
				<td align="left" valign="top" width = "40%">Drivers Licence State:</td>

				<td align="left" valign="top"><input type="text" name="dlstate"
					maxlength="50" size="20"></td>
			</tr>

			<tr>
				<td align="left" valign="top">Drivers Licence Num:</td>

				<td align="left" valign="top"><input type="text" name="dlnum"
					maxlength="50" size="20"></td>
			</tr>

			<tr>
				<td align="left" valign="top">First Name:</td>

				<td align="left" valign="top"><input type="text" name="fname"
					maxlength="50" size="20"></td>
			</tr>

			<tr>
				<td align="left" valign="top">Last Name:</td>

				<td align="left" valign="top"><input type="text" name="lname"
					maxlength="50" size="20"></td>
			</tr>

			<tr>
				<td align="left" valign="top">Street Number, Name:</td>

				<td align="left" valign="top"><input type="text" name="street"
					maxlength="50" size="20"></td>
			</tr>

			<tr>
				<td align="left" valign="top">City:</td>

				<td align="left" valign="top"><input type="text" name="city"
					maxlength="50" size="20"></td>
			</tr>

			<tr>
				<td align="left" valign="top">State:</td>

				<td align="left" valign="top"><input type="text" name="state"
					maxlength="20" size="20"></td>
			</tr>

			<tr>
				<td align="left" valign="top">Postal Code:</td>

				<td align="left" valign="top"><input type="text" name="pcode"
					maxlength="10" size="20"></td>
			</tr>

			<tr>
				<td align="left" valign="top">Phone:</td>

				<td align="left" valign="top"><input type="text" name="phone"
					maxlength="20" size="20"></td>
			</tr>

			<tr>
				<td align="left" valign="top">Email:</td>

				<td align="left" valign="top"><input type="text" name="email"
					maxlength="20" size="20"></td>
			</tr>

			<tr>
				<td align="left" valign="top">Password:</td>

				<td align="left" valign="top"><input type="password"
					name="password" maxlength="20" size="20"></td>
			</tr>
		</table>
		</td>
	</tr>
	<tr>
		<td width="20%"></td>
		<td bgcolor="red" align = "center"><input type="submit" value="Register"
			name="register"></td>
	</tr>
</table>
</form>
<%=tags.getFooter()%>
</body>
</html>

