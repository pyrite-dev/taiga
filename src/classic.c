#include <taiga.h>

void classic_stylesheet(FILE* out){
	fprintf(out, "body {\n");
	fprintf(out, "	padding: 0;\n");
	fprintf(out, "	margin: 0;\n");
	fprintf(out, "	font-family: Arial, sans-serif;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#breadcrumb {\n");
	fprintf(out, "	background-color: #600000;\n");
	fprintf(out, "	font-weight: bold;\n");
	fprintf(out, "	color: #fff;\n");
	fprintf(out, "	padding-left: 8px;\n");
	fprintf(out, "	padding-top: 2px;\n");
	fprintf(out, "	padding-bottom: 2px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#nav {\n");
	fprintf(out, "	background-color: #eeeeee;\n");
	fprintf(out, "	border-right: solid 1px #aaaaaa;\n");
	fprintf(out, "	border-bottom: solid 1px #aaaaaa;\n");
	fprintf(out, "	padding: 8px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#content {\n");
	fprintf(out, "	padding: 8px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".section {\n");
	fprintf(out, "	background-color: #eeeeee;\n");
	fprintf(out, "	padding-left: 8px;\n");
	fprintf(out, "	font-weight: bold;\n");
	fprintf(out, "	color: #000088;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "a {\n");
	fprintf(out, "	text-decoration: none;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#breadcrumb a {\n");
	fprintf(out, "	color: #ffff44;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "a:link {\n");
	fprintf(out, "	color: #003366;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "a:visited {\n");
	fprintf(out, "	color: blue;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "a:hover, #breadcrumb a:hover {\n");
	fprintf(out, "	color: #ff3300;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".linkgroup {\n");
	fprintf(out, "	padding-left: 16px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, ".linkgrouptitle {\n");
	fprintf(out, "	font-weight: bold;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "#content p {\n");
	fprintf(out, "	padding-left: 8px;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "tr.even {\n");
	fprintf(out, "	background-color: #eeeeee;\n");
	fprintf(out, "}\n");
	fprintf(out, "\n");
	fprintf(out, "tr.odd {\n");
	fprintf(out, "	background-color: #dddddd;\n");
	fprintf(out, "}\n");
}

void classic_head(FILE* out, const char* top, xl_node_t* header){
	fprintf(out, "		<link rel=\"stylesheet\" href=\"%sstyle.css\">\n", top);
}

void classic_body(FILE* out, const char* top, const char* title, xl_node_t* body){
}
