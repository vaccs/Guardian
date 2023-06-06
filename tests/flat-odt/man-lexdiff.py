
from sys import argv;

import os;
import subprocess;

def run(command):
  print("\033[33m" f" $ {' '.join(command)}" "\033[0m");
  result = subprocess.run(command, \
    capture_output = True, text = True, \
    env = os.environ.update({"print_stacktrace": "1", "halt_on_error": "1"}))
  if result.returncode:
    print("\033[31m" " subcommand failed!");
    exit(1);

executable = argv[1];

run([executable, "-i", "./examples/flat-odt.guard", "-o", "/tmp/flat-odt.c"]);

run(["gcc", "-Werror", "-Wall", "/tmp/flat-odt.c", "-o", "/tmp/flat-odt", "-lgmp"]);

with open("/tmp/man-lexdiff.txt", "w") as stream:
    stream.write("""
<?xml version="1.0" encoding="UTF-8"?>

<office:document xmlns:officeooo="http://openoffice.org/2009/office" xmlns:css3t="http://www.w3.org/TR/css3-text/" xmlns:grddl="http://www.w3.org/2003/g/data-view#" xmlns:xhtml="http://www.w3.org/1999/xhtml" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:chart="urn:oasis:names:tc:opendocument:xmlns:chart:1.0" xmlns:svg="urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0" xmlns:draw="urn:oasis:names:tc:opendocument:xmlns:drawing:1.0" xmlns:rpt="http://openoffice.org/2005/report" xmlns:text="urn:oasis:names:tc:opendocument:xmlns:text:1.0" xmlns:style="urn:oasis:names:tc:opendocument:xmlns:style:1.0" xmlns:meta="urn:oasis:names:tc:opendocument:xmlns:meta:1.0" xmlns:config="urn:oasis:names:tc:opendocument:xmlns:config:1.0" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:fo="urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0" xmlns:of="urn:oasis:names:tc:opendocument:xmlns:of:1.2" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:ooo="http://openoffice.org/2004/office" xmlns:dr3d="urn:oasis:names:tc:opendocument:xmlns:dr3d:1.0" xmlns:formx="urn:openoffice:names:experimental:ooxml-odf-interop:xmlns:form:1.0" xmlns:calcext="urn:org:documentfoundation:names:experimental:calc:xmlns:calcext:1.0" xmlns:drawooo="http://openoffice.org/2010/draw" xmlns:field="urn:openoffice:names:experimental:ooo-ms-interop:xmlns:field:1.0" xmlns:office="urn:oasis:names:tc:opendocument:xmlns:office:1.0" xmlns:table="urn:oasis:names:tc:opendocument:xmlns:table:1.0" xmlns:number="urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0" xmlns:ooow="http://openoffice.org/2004/writer" xmlns:oooc="http://openoffice.org/2004/calc" xmlns:tableooo="http://openoffice.org/2009/table" xmlns:loext="urn:org:documentfoundation:names:experimental:office:xmlns:loext:1.0" xmlns:math="http://www.w3.org/1998/Math/MathML" xmlns:form="urn:oasis:names:tc:opendocument:xmlns:form:1.0" xmlns:script="urn:oasis:names:tc:opendocument:xmlns:script:1.0" xmlns:dom="http://www.w3.org/2001/xml-events" xmlns:xforms="http://www.w3.org/2002/xforms" office:version="1.2" office:mimetype="application/vnd.oasis.opendocument.text">
 <office:meta><meta:creation-date>2023-05-06T13:00:49.125398167</meta:creation-date><dc:date>2023-05-06T13:46:12.940217235</dc:date><meta:editing-duration>PT21S</meta:editing-duration><meta:editing-cycles>1</meta:editing-cycles><meta:document-statistic meta:table-count="0" meta:image-count="0" meta:object-count="0" meta:page-count="1" meta:paragraph-count="75" meta:word-count="994" meta:character-count="6360" meta:non-whitespace-character-count="5222"/><meta:generator>LibreOffice/6.4.7.2$Linux_X86_64 LibreOffice_project/40$Build-2</meta:generator></office:meta>
 <office:settings>
  <config:config-item-set config:name="ooo:view-settings">
   <config:config-item config:name="ViewAreaTop" config:type="long">568</config:config-item>
   <config:config-item config:name="ViewAreaLeft" config:type="long">501</config:config-item>
   <config:config-item config:name="ViewAreaWidth" config:type="long">51864</config:config-item>
   <config:config-item config:name="ViewAreaHeight" config:type="long">26827</config:config-item>
   <config:config-item config:name="ShowRedlineChanges" config:type="boolean">true</config:config-item>
   <config:config-item config:name="InBrowseMode" config:type="boolean">true</config:config-item>
   <config:config-item-map-indexed config:name="Views">
    <config:config-item-map-entry>
     <config:config-item config:name="ViewId" config:type="string">view2</config:config-item>
     <config:config-item config:name="ViewLeft" config:type="long">1995</config:config-item>
     <config:config-item config:name="ViewTop" config:type="long">58120</config:config-item>
     <config:config-item config:name="VisibleLeft" config:type="long">501</config:config-item>
     <config:config-item config:name="VisibleTop" config:type="long">568</config:config-item>
     <config:config-item config:name="VisibleRight" config:type="long">52363</config:config-item>
     <config:config-item config:name="VisibleBottom" config:type="long">27393</config:config-item>
     <config:config-item config:name="ZoomType" config:type="short">0</config:config-item>
     <config:config-item config:name="ViewLayoutColumns" config:type="short">1</config:config-item>
     <config:config-item config:name="ViewLayoutBookMode" config:type="boolean">false</config:config-item>
     <config:config-item config:name="ZoomFactor" config:type="short">90</config:config-item>
     <config:config-item config:name="IsSelectedFrame" config:type="boolean">false</config:config-item>
     <config:config-item config:name="AnchoredTextOverflowLegacy" config:type="boolean">false</config:config-item>
    </config:config-item-map-entry>
   </config:config-item-map-indexed>
  </config:config-item-set>
  <config:config-item-set config:name="ooo:configuration-settings">
   <config:config-item config:name="PrintProspect" config:type="boolean">false</config:config-item>
   <config:config-item config:name="PrintReversed" config:type="boolean">false</config:config-item>
   <config:config-item config:name="PrintSingleJobs" config:type="boolean">false</config:config-item>
   <config:config-item config:name="PrintLeftPages" config:type="boolean">true</config:config-item>
   <config:config-item config:name="PrintTables" config:type="boolean">true</config:config-item>
   <config:config-item config:name="PrintControls" config:type="boolean">true</config:config-item>
   <config:config-item config:name="PrintPageBackground" config:type="boolean">true</config:config-item>
   <config:config-item config:name="PrintDrawings" config:type="boolean">true</config:config-item>
   <config:config-item config:name="PrintBlackFonts" config:type="boolean">false</config:config-item>
   <config:config-item config:name="PrintAnnotationMode" config:type="short">0</config:config-item>
   <config:config-item config:name="PrintTextPlaceholder" config:type="boolean">false</config:config-item>
   <config:config-item config:name="EmptyDbFieldHidesPara" config:type="boolean">true</config:config-item>
   <config:config-item config:name="DisableOffPagePositioning" config:type="boolean">false</config:config-item>
   <config:config-item config:name="SubtractFlysAnchoredAtFlys" config:type="boolean">false</config:config-item>
   <config:config-item config:name="PropLineSpacingShrinksFirstLine" config:type="boolean">true</config:config-item>
   <config:config-item config:name="ApplyParagraphMarkFormatToNumbering" config:type="boolean">false</config:config-item>
   <config:config-item config:name="TreatSingleColumnBreakAsPageBreak" config:type="boolean">false</config:config-item>
   <config:config-item config:name="EmbedSystemFonts" config:type="boolean">false</config:config-item>
   <config:config-item config:name="EmbedComplexScriptFonts" config:type="boolean">true</config:config-item>
   <config:config-item config:name="EmbedAsianScriptFonts" config:type="boolean">true</config:config-item>
   <config:config-item config:name="EmbedLatinScriptFonts" config:type="boolean">true</config:config-item>
   <config:config-item config:name="EmbedOnlyUsedFonts" config:type="boolean">false</config:config-item>
   <config:config-item config:name="ContinuousEndnotes" config:type="boolean">false</config:config-item>
   <config:config-item config:name="EmbedFonts" config:type="boolean">false</config:config-item>
   <config:config-item config:name="ClippedPictures" config:type="boolean">false</config:config-item>
   <config:config-item config:name="FloattableNomargins" config:type="boolean">false</config:config-item>
   <config:config-item config:name="UnbreakableNumberings" config:type="boolean">false</config:config-item>
   <config:config-item config:name="HeaderSpacingBelowLastPara" config:type="boolean">false</config:config-item>
   <config:config-item config:name="AllowPrintJobCancel" config:type="boolean">true</config:config-item>
   <config:config-item config:name="UseOldPrinterMetrics" config:type="boolean">false</config:config-item>
   <config:config-item config:name="TabOverMargin" config:type="boolean">false</config:config-item>
   <config:config-item config:name="TabsRelativeToIndent" config:type="boolean">true</config:config-item>
   <config:config-item config:name="UseOldNumbering" config:type="boolean">false</config:config-item>
   <config:config-item config:name="InvertBorderSpacing" config:type="boolean">false</config:config-item>
   <config:config-item config:name="PrintPaperFromSetup" config:type="boolean">false</config:config-item>
   <config:config-item config:name="UpdateFromTemplate" config:type="boolean">true</config:config-item>
   <config:config-item config:name="CurrentDatabaseCommandType" config:type="int">0</config:config-item>
   <config:config-item config:name="LinkUpdateMode" config:type="short">1</config:config-item>
   <config:config-item config:name="AddParaSpacingToTableCells" config:type="boolean">true</config:config-item>
   <config:config-item config:name="CurrentDatabaseCommand" config:type="string"/>
   <config:config-item config:name="PrinterIndependentLayout" config:type="string">high-resolution</config:config-item>
   <config:config-item config:name="ApplyUserData" config:type="boolean">true</config:config-item>
   <config:config-item config:name="PrintFaxName" config:type="string"/>
   <config:config-item config:name="CurrentDatabaseDataSource" config:type="string"/>
   <config:config-item config:name="ClipAsCharacterAnchoredWriterFlyFrames" config:type="boolean">false</config:config-item>
   <config:config-item config:name="IsKernAsianPunctuation" config:type="boolean">false</config:config-item>
   <config:config-item config:name="SaveThumbnail" config:type="boolean">true</config:config-item>
   <config:config-item config:name="UseFormerTextWrapping" config:type="boolean">false</config:config-item>
   <config:config-item config:name="AddExternalLeading" config:type="boolean">true</config:config-item>
   <config:config-item config:name="AddParaTableSpacing" config:type="boolean">true</config:config-item>
   <config:config-item config:name="StylesNoDefault" config:type="boolean">false</config:config-item>
   <config:config-item config:name="ChartAutoUpdate" config:type="boolean">true</config:config-item>
   <config:config-item config:name="PrinterSetup" config:type="base64Binary"/>
   <config:config-item config:name="AddParaTableSpacingAtStart" config:type="boolean">true</config:config-item>
   <config:config-item config:name="Rsid" config:type="int">915454</config:config-item>
   <config:config-item config:name="EmbeddedDatabaseName" config:type="string"/>
   <config:config-item config:name="FieldAutoUpdate" config:type="boolean">true</config:config-item>
   <config:config-item config:name="OutlineLevelYieldsNumbering" config:type="boolean">false</config:config-item>
   <config:config-item config:name="AlignTabStopPosition" config:type="boolean">true</config:config-item>
   <config:config-item config:name="CharacterCompressionType" config:type="short">0</config:config-item>
   <config:config-item config:name="PrinterName" config:type="string"/>
   <config:config-item config:name="SaveGlobalDocumentLinks" config:type="boolean">false</config:config-item>
   <config:config-item config:name="PrinterPaperFromSetup" config:type="boolean">false</config:config-item>
   <config:config-item config:name="UseFormerLineSpacing" config:type="boolean">false</config:config-item>
   <config:config-item config:name="AddParaLineSpacingToTableCells" config:type="boolean">true</config:config-item>
   <config:config-item config:name="UseFormerObjectPositioning" config:type="boolean">false</config:config-item>
   <config:config-item config:name="PrintGraphics" config:type="boolean">true</config:config-item>
   <config:config-item config:name="SurroundTextWrapSmall" config:type="boolean">false</config:config-item>
   <config:config-item config:name="ConsiderTextWrapOnObjPos" config:type="boolean">false</config:config-item>
   <config:config-item config:name="MsWordCompTrailingBlanks" config:type="boolean">false</config:config-item>
   <config:config-item config:name="TabAtLeftIndentForParagraphsInList" config:type="boolean">false</config:config-item>
   <config:config-item config:name="PrintRightPages" config:type="boolean">true</config:config-item>
   <config:config-item config:name="IgnoreFirstLineIndentInNumbering" config:type="boolean">false</config:config-item>
   <config:config-item config:name="RedlineProtectionKey" config:type="base64Binary"/>
   <config:config-item config:name="DoNotJustifyLinesWithManualBreak" config:type="boolean">false</config:config-item>
   <config:config-item config:name="PrintProspectRTL" config:type="boolean">false</config:config-item>
   <config:config-item config:name="PrintEmptyPages" config:type="boolean">true</config:config-item>
   <config:config-item config:name="DoNotResetParaAttrsForNumFont" config:type="boolean">false</config:config-item>
   <config:config-item config:name="AddFrameOffsets" config:type="boolean">false</config:config-item>
   <config:config-item config:name="IgnoreTabsAndBlanksForLineCalculation" config:type="boolean">false</config:config-item>
   <config:config-item config:name="LoadReadonly" config:type="boolean">false</config:config-item>
   <config:config-item config:name="DoNotCaptureDrawObjsOnPage" config:type="boolean">false</config:config-item>
   <config:config-item config:name="AddVerticalFrameOffsets" config:type="boolean">false</config:config-item>
   <config:config-item config:name="UnxForceZeroExtLeading" config:type="boolean">false</config:config-item>
   <config:config-item config:name="IsLabelDocument" config:type="boolean">false</config:config-item>
   <config:config-item config:name="TableRowKeep" config:type="boolean">false</config:config-item>
   <config:config-item config:name="RsidRoot" config:type="int">645875</config:config-item>
   <config:config-item config:name="PrintHiddenText" config:type="boolean">false</config:config-item>
   <config:config-item config:name="ProtectForm" config:type="boolean">false</config:config-item>
   <config:config-item config:name="MsWordCompMinLineHeightByFly" config:type="boolean">false</config:config-item>
   <config:config-item config:name="BackgroundParaOverDrawings" config:type="boolean">false</config:config-item>
   <config:config-item config:name="SaveVersionOnClose" config:type="boolean">false</config:config-item>
   <config:config-item config:name="MathBaselineAlignment" config:type="boolean">true</config:config-item>
   <config:config-item config:name="SmallCapsPercentage66" config:type="boolean">false</config:config-item>
   <config:config-item config:name="CollapseEmptyCellPara" config:type="boolean">true</config:config-item>
   <config:config-item config:name="TabOverflow" config:type="boolean">true</config:config-item>
  </config:config-item-set>
 </office:settings>
 <office:scripts>
  <office:script script:language="ooo:Basic">
   <ooo:libraries xmlns:ooo="http://openoffice.org/2004/office" xmlns:xlink="http://www.w3.org/1999/xlink">
    <ooo:library-embedded ooo:name="Standard"/>
   </ooo:libraries>
  </office:script>
 </office:scripts>
 <office:font-face-decls>
  <style:font-face style:name="OpenSymbol" svg:font-family="OpenSymbol" style:font-charset="x-symbol"/>
  <style:font-face style:name="Lohit Devanagari1" svg:font-family="&apos;Lohit Devanagari&apos;"/>
  <style:font-face style:name="monospace" svg:font-family="monospace"/>
  <style:font-face style:name="DejaVu Sans Mono" svg:font-family="&apos;DejaVu Sans Mono&apos;" style:font-adornments="Book" style:font-family-generic="modern" style:font-pitch="fixed"/>
  <style:font-face style:name="Liberation Mono" svg:font-family="&apos;Liberation Mono&apos;" style:font-family-generic="modern" style:font-pitch="fixed"/>
  <style:font-face style:name="Noto Sans Mono CJK SC" svg:font-family="&apos;Noto Sans Mono CJK SC&apos;" style:font-family-generic="modern" style:font-pitch="fixed"/>
  <style:font-face style:name="Liberation Serif" svg:font-family="&apos;Liberation Serif&apos;" style:font-family-generic="roman" style:font-pitch="variable"/>
  <style:font-face style:name="Lohit Devanagari" svg:font-family="&apos;Lohit Devanagari&apos;" style:font-family-generic="system" style:font-pitch="variable"/>
  <style:font-face style:name="Noto Sans CJK SC" svg:font-family="&apos;Noto Sans CJK SC&apos;" style:font-family-generic="system" style:font-pitch="variable"/>
  <style:font-face style:name="Noto Serif CJK SC" svg:font-family="&apos;Noto Serif CJK SC&apos;" style:font-family-generic="system" style:font-pitch="variable"/>
 </office:font-face-decls>
 <office:styles>
  <style:default-style style:family="graphic">
   <style:graphic-properties svg:stroke-color="#3465a4" draw:fill-color="#729fcf" fo:wrap-option="no-wrap" draw:shadow-offset-x="0.1181in" draw:shadow-offset-y="0.1181in" draw:start-line-spacing-horizontal="0.1114in" draw:start-line-spacing-vertical="0.1114in" draw:end-line-spacing-horizontal="0.1114in" draw:end-line-spacing-vertical="0.1114in" style:flow-with-text="false"/>
   <style:paragraph-properties style:text-autospace="ideograph-alpha" style:line-break="strict" style:writing-mode="lr-tb" style:font-independent-line-spacing="false">
    <style:tab-stops/>
   </style:paragraph-properties>
   <style:text-properties style:use-window-font-color="true" style:font-name="Liberation Serif" fo:font-size="12pt" fo:language="en" fo:country="US" style:letter-kerning="true" style:font-name-asian="Noto Serif CJK SC" style:font-size-asian="10.5pt" style:language-asian="zh" style:country-asian="CN" style:font-name-complex="Lohit Devanagari" style:font-size-complex="12pt" style:language-complex="hi" style:country-complex="IN"/>
  </style:default-style>
  <style:default-style style:family="paragraph">
   <style:paragraph-properties fo:orphans="2" fo:widows="2" fo:hyphenation-ladder-count="no-limit" style:text-autospace="ideograph-alpha" style:punctuation-wrap="hanging" style:line-break="strict" style:tab-stop-distance="0.4925in" style:writing-mode="page"/>
   <style:text-properties style:use-window-font-color="true" style:font-name="Liberation Serif" fo:font-size="12pt" fo:language="en" fo:country="US" style:letter-kerning="true" style:font-name-asian="Noto Serif CJK SC" style:font-size-asian="10.5pt" style:language-asian="zh" style:country-asian="CN" style:font-name-complex="Lohit Devanagari" style:font-size-complex="12pt" style:language-complex="hi" style:country-complex="IN" fo:hyphenate="false" fo:hyphenation-remain-char-count="2" fo:hyphenation-push-char-count="2" loext:hyphenation-no-caps="false"/>
  </style:default-style>
  <style:default-style style:family="table">
   <style:table-properties table:border-model="collapsing"/>
  </style:default-style>
  <style:default-style style:family="table-row">
   <style:table-row-properties fo:keep-together="auto"/>
  </style:default-style>
  <style:style style:name="Standard" style:family="paragraph" style:class="text" style:master-page-name="">
   <style:paragraph-properties style:page-number="auto"/>
   <style:text-properties fo:color="#ffffff" style:font-name="DejaVu Sans Mono" fo:font-family="&apos;DejaVu Sans Mono&apos;" style:font-style-name="Book" style:font-family-generic="modern" style:font-pitch="fixed" fo:font-size="10pt"/>
  </style:style>
  <style:style style:name="Heading" style:family="paragraph" style:parent-style-name="Standard" style:next-style-name="Text_20_body" style:class="text">
   <style:paragraph-properties fo:margin-top="0.1665in" fo:margin-bottom="0.0835in" loext:contextual-spacing="false" fo:keep-with-next="always"/>
   <style:text-properties style:font-name="DejaVu Sans Mono" fo:font-family="&apos;DejaVu Sans Mono&apos;" style:font-style-name="Book" style:font-family-generic="modern" style:font-pitch="fixed" fo:font-size="10pt" style:font-name-asian="Noto Sans CJK SC" style:font-family-asian="&apos;Noto Sans CJK SC&apos;" style:font-family-generic-asian="system" style:font-pitch-asian="variable" style:font-size-asian="14pt" style:font-name-complex="Lohit Devanagari" style:font-family-complex="&apos;Lohit Devanagari&apos;" style:font-family-generic-complex="system" style:font-pitch-complex="variable" style:font-size-complex="14pt"/>
  </style:style>
  <style:style style:name="Text_20_body" style:display-name="Text body" style:family="paragraph" style:parent-style-name="Standard" style:class="text">
   <style:paragraph-properties fo:margin-left="0.5in" fo:margin-right="0.5in" fo:margin-top="0.1in" fo:margin-bottom="0.1in" loext:contextual-spacing="false" fo:line-height="115%" fo:text-indent="0in" style:auto-text-indent="false"/>
   <style:text-properties fo:font-size="10pt" officeooo:rsid="0009daf3"/>
  </style:style>
  <style:style style:name="List" style:family="paragraph" style:parent-style-name="Text_20_body" style:class="list" style:master-page-name="">
   <style:paragraph-properties fo:margin-left="0in" fo:margin-right="0in" fo:margin-top="0in" fo:margin-bottom="0.1in" loext:contextual-spacing="true" fo:text-indent="0in" style:auto-text-indent="false" style:page-number="auto"/>
   <style:text-properties style:font-size-asian="12pt" style:font-name-complex="Lohit Devanagari1" style:font-family-complex="&apos;Lohit Devanagari&apos;"/>
  </style:style>
  <style:style style:name="Caption" style:family="paragraph" style:parent-style-name="Standard" style:class="extra">
   <style:paragraph-properties fo:margin-top="0.0835in" fo:margin-bottom="0.0835in" loext:contextual-spacing="false" text:number-lines="false" text:line-number="0"/>
   <style:text-properties fo:font-size="12pt" fo:font-style="italic" style:font-size-asian="12pt" style:font-style-asian="italic" style:font-name-complex="Lohit Devanagari1" style:font-family-complex="&apos;Lohit Devanagari&apos;" style:font-size-complex="12pt" style:font-style-complex="italic"/>
  </style:style>
  <style:style style:name="Index" style:family="paragraph" style:parent-style-name="Standard" style:class="index">
   <style:paragraph-properties text:number-lines="false" text:line-number="0"/>
   <style:text-properties style:font-size-asian="12pt" style:font-name-complex="Lohit Devanagari1" style:font-family-complex="&apos;Lohit Devanagari&apos;"/>
  </style:style>
  <style:style style:name="Heading_20_1" style:display-name="Heading 1" style:family="paragraph" style:parent-style-name="Heading" style:next-style-name="Text_20_body" style:auto-update="true" style:default-outline-level="1" style:class="text" style:master-page-name="">
   <style:paragraph-properties fo:margin-left="0in" fo:margin-right="0in" fo:margin-top="0in" fo:margin-bottom="0in" loext:contextual-spacing="false" fo:text-indent="0in" style:auto-text-indent="false" style:page-number="auto"/>
   <style:text-properties fo:text-transform="uppercase" fo:font-size="10pt" fo:font-weight="bold" style:font-size-asian="130%" style:font-weight-asian="bold" style:font-size-complex="130%" style:font-weight-complex="bold"/>
  </style:style>
  <style:style style:name="Heading_20_2" style:display-name="Heading 2" style:family="paragraph" style:parent-style-name="Heading" style:next-style-name="Text_20_body" style:default-outline-level="2" style:class="text">
   <style:paragraph-properties fo:margin-left="0.25in" fo:margin-right="0in" fo:margin-top="0.139in" fo:margin-bottom="0.0835in" loext:contextual-spacing="false" fo:text-indent="0in" style:auto-text-indent="false"/>
   <style:text-properties fo:font-size="10pt" fo:font-weight="bold" style:font-size-asian="115%" style:font-weight-asian="bold" style:font-size-complex="115%" style:font-weight-complex="bold"/>
  </style:style>
  <style:style style:name="List_20_1" style:display-name="List 1" style:family="paragraph" style:parent-style-name="List" style:class="list">
   <style:paragraph-properties fo:margin-left="0.25in" fo:margin-right="0in" fo:margin-top="0in" fo:margin-bottom="0.0835in" loext:contextual-spacing="false" fo:line-height="100%" fo:text-indent="-0.25in" style:auto-text-indent="false"/>
  </style:style>
  <style:style style:name="List_20_Indent" style:display-name="List Indent" style:family="paragraph" style:parent-style-name="Text_20_body" style:class="text">
   <style:paragraph-properties fo:margin-left="0in" fo:margin-right="0in" fo:text-indent="0in" style:auto-text-indent="false">
    <style:tab-stops>
     <style:tab-stop style:position="0in"/>
    </style:tab-stops>
   </style:paragraph-properties>
  </style:style>
  <style:style style:name="Quotations" style:family="paragraph" style:parent-style-name="Standard" style:class="html">
   <style:paragraph-properties fo:margin-left="0.75in" fo:margin-right="0.75in" fo:margin-top="0in" fo:margin-bottom="0.1965in" loext:contextual-spacing="false" fo:text-indent="0in" style:auto-text-indent="false" fo:padding="0.0201in" fo:border="2.01pt solid #ffffff">
    <style:tab-stops/>
   </style:paragraph-properties>
   <style:text-properties fo:background-color="transparent"/>
  </style:style>
  <style:style style:name="Preformatted_20_Text" style:display-name="Preformatted Text" style:family="paragraph" style:parent-style-name="Standard" style:class="html" style:master-page-name="">
   <style:paragraph-properties fo:margin-left="0.75in" fo:margin-right="0.75in" fo:margin-top="0in" fo:margin-bottom="0in" loext:contextual-spacing="false" fo:text-align="start" style:justify-single-word="false" fo:text-indent="0in" style:auto-text-indent="false" style:page-number="auto" fo:padding="0.15in" fo:border="2.01pt solid #ffffff" style:join-border="true"/>
   <style:text-properties style:font-name="Liberation Mono" fo:font-family="&apos;Liberation Mono&apos;" style:font-family-generic="modern" style:font-pitch="fixed" fo:font-size="10pt" style:font-name-asian="Noto Sans Mono CJK SC" style:font-family-asian="&apos;Noto Sans Mono CJK SC&apos;" style:font-family-generic-asian="modern" style:font-pitch-asian="fixed" style:font-size-asian="10pt" style:font-name-complex="Liberation Mono" style:font-family-complex="&apos;Liberation Mono&apos;" style:font-family-generic-complex="modern" style:font-pitch-complex="fixed" style:font-size-complex="10pt"/>
  </style:style>
  <style:style style:name="List_20_Contents" style:display-name="List Contents" style:family="paragraph" style:parent-style-name="Standard" style:class="html">
   <style:paragraph-properties fo:margin-left="0.5in" fo:margin-right="0in" fo:margin-top="0in" fo:margin-bottom="0in" loext:contextual-spacing="true" fo:text-indent="0in" style:auto-text-indent="false"/>
  </style:style>
  <style:style style:name="Bullet_20_Symbols" style:display-name="Bullet Symbols" style:family="text">
   <style:text-properties style:font-name="OpenSymbol" fo:font-family="OpenSymbol" style:font-charset="x-symbol" style:font-name-asian="OpenSymbol" style:font-family-asian="OpenSymbol" style:font-charset-asian="x-symbol" style:font-name-complex="OpenSymbol" style:font-family-complex="OpenSymbol" style:font-charset-complex="x-symbol"/>
  </style:style>
  <style:style style:name="Numbering_20_Symbols" style:display-name="Numbering Symbols" style:family="text"/>
  <style:style style:name="Internet_20_link" style:display-name="Internet link" style:family="text">
   <style:text-properties fo:color="#000080" fo:language="zxx" fo:country="none" style:text-underline-style="solid" style:text-underline-width="auto" style:text-underline-color="font-color" style:language-asian="zxx" style:country-asian="none" style:language-complex="zxx" style:country-complex="none"/>
  </style:style>
  <text:outline-style style:name="Outline">
   <text:outline-level-style text:level="1" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab"/>
    </style:list-level-properties>
   </text:outline-level-style>
   <text:outline-level-style text:level="2" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab"/>
    </style:list-level-properties>
   </text:outline-level-style>
   <text:outline-level-style text:level="3" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab"/>
    </style:list-level-properties>
   </text:outline-level-style>
   <text:outline-level-style text:level="4" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab"/>
    </style:list-level-properties>
   </text:outline-level-style>
   <text:outline-level-style text:level="5" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab"/>
    </style:list-level-properties>
   </text:outline-level-style>
   <text:outline-level-style text:level="6" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab"/>
    </style:list-level-properties>
   </text:outline-level-style>
   <text:outline-level-style text:level="7" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab"/>
    </style:list-level-properties>
   </text:outline-level-style>
   <text:outline-level-style text:level="8" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab"/>
    </style:list-level-properties>
   </text:outline-level-style>
   <text:outline-level-style text:level="9" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab"/>
    </style:list-level-properties>
   </text:outline-level-style>
   <text:outline-level-style text:level="10" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab"/>
    </style:list-level-properties>
   </text:outline-level-style>
  </text:outline-style>
  <text:notes-configuration text:note-class="footnote" style:num-format="1" text:start-value="0" text:footnotes-position="page" text:start-numbering-at="document"/>
  <text:notes-configuration text:note-class="endnote" style:num-format="i" text:start-value="0"/>
  <text:linenumbering-configuration text:number-lines="false" text:offset="0.1965in" style:num-format="1" text:number-position="left" text:increment="5"/>
 </office:styles>
 <office:automatic-styles>
  <style:style style:name="P1" style:family="paragraph" style:parent-style-name="Heading_20_1">
   <style:text-properties officeooo:paragraph-rsid="0009daf3"/>
  </style:style>
  <style:style style:name="P2" style:family="paragraph" style:parent-style-name="Text_20_body">
   <style:text-properties officeooo:rsid="0009daf3" officeooo:paragraph-rsid="0009daf3"/>
  </style:style>
  <style:style style:name="P3" style:family="paragraph" style:parent-style-name="Text_20_body" style:list-style-name="L2">
   <style:text-properties officeooo:rsid="0009daf3" officeooo:paragraph-rsid="000ba5f7"/>
  </style:style>
  <style:style style:name="P4" style:family="paragraph" style:parent-style-name="Text_20_body" style:list-style-name="L1">
   <style:text-properties officeooo:rsid="000a02a9" officeooo:paragraph-rsid="000a02a9"/>
  </style:style>
  <style:style style:name="P5" style:family="paragraph" style:parent-style-name="Text_20_body" style:list-style-name="L1">
   <style:text-properties officeooo:paragraph-rsid="000a02a9"/>
  </style:style>
  <style:style style:name="P6" style:family="paragraph" style:parent-style-name="Text_20_body" style:list-style-name="L2">
   <style:text-properties officeooo:paragraph-rsid="000ba5f7"/>
  </style:style>
  <style:style style:name="P7" style:family="paragraph" style:parent-style-name="Text_20_body">
   <style:text-properties officeooo:paragraph-rsid="000d1f0f"/>
  </style:style>
  <style:style style:name="P8" style:family="paragraph" style:parent-style-name="Text_20_body">
   <style:paragraph-properties fo:margin-left="0in" fo:margin-right="0.5in" fo:text-indent="0in" style:auto-text-indent="false"/>
   <style:text-properties officeooo:rsid="0009daf3" officeooo:paragraph-rsid="0009daf3"/>
  </style:style>
  <style:style style:name="T1" style:family="text">
   <style:text-properties officeooo:rsid="0009daf3"/>
  </style:style>
  <style:style style:name="T2" style:family="text">
   <style:text-properties fo:color="#00a933"/>
  </style:style>
  <style:style style:name="T3" style:family="text">
   <style:text-properties fo:color="#00ffff"/>
  </style:style>
  <style:style style:name="T4" style:family="text">
   <style:text-properties fo:color="#ff0000"/>
  </style:style>
  <style:style style:name="T5" style:family="text">
   <style:text-properties fo:color="#ff6d6d"/>
  </style:style>
  <style:style style:name="T6" style:family="text">
   <style:text-properties officeooo:rsid="000d1f0f"/>
  </style:style>
  <style:style style:name="T7" style:family="text">
   <style:text-properties fo:color="#ffffff" style:font-name="DejaVu Sans Mono" fo:font-size="10pt" officeooo:rsid="000d1f0f"/>
  </style:style>
  <style:style style:name="T8" style:family="text">
   <style:text-properties fo:color="#158466"/>
  </style:style>
  <style:style style:name="T9" style:family="text">
   <style:text-properties fo:color="#b2b2b2"/>
  </style:style>
  <text:list-style style:name="L1">
   <text:list-level-style-number text:level="1" text:style-name="Numbering_20_Symbols" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="1in" fo:text-indent="-0.5in" fo:margin-left="1in"/>
    </style:list-level-properties>
   </text:list-level-style-number>
   <text:list-level-style-bullet text:level="2" text:style-name="Bullet_20_Symbols" text:bullet-char="◦">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="1.25in" fo:text-indent="-1.2402in" fo:margin-left="1.25in"/>
    </style:list-level-properties>
   </text:list-level-style-bullet>
   <text:list-level-style-bullet text:level="3" text:style-name="Bullet_20_Symbols" text:bullet-char="▪">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="1.5in" fo:text-indent="-1.4902in" fo:margin-left="1.5in"/>
    </style:list-level-properties>
   </text:list-level-style-bullet>
   <text:list-level-style-bullet text:level="4" text:style-name="Bullet_20_Symbols" text:bullet-char="•">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="1.75in" fo:text-indent="-1.7402in" fo:margin-left="1.75in"/>
    </style:list-level-properties>
   </text:list-level-style-bullet>
   <text:list-level-style-bullet text:level="5" text:style-name="Bullet_20_Symbols" text:bullet-char="◦">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="2in" fo:text-indent="-1.9902in" fo:margin-left="2in"/>
    </style:list-level-properties>
   </text:list-level-style-bullet>
   <text:list-level-style-bullet text:level="6" text:style-name="Bullet_20_Symbols" text:bullet-char="▪">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="2.25in" fo:text-indent="-2.2402in" fo:margin-left="2.25in"/>
    </style:list-level-properties>
   </text:list-level-style-bullet>
   <text:list-level-style-bullet text:level="7" text:style-name="Bullet_20_Symbols" text:bullet-char="•">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="2.5in" fo:text-indent="-2.4902in" fo:margin-left="2.5in"/>
    </style:list-level-properties>
   </text:list-level-style-bullet>
   <text:list-level-style-bullet text:level="8" text:style-name="Bullet_20_Symbols" text:bullet-char="◦">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="2.75in" fo:text-indent="-2.7402in" fo:margin-left="2.75in"/>
    </style:list-level-properties>
   </text:list-level-style-bullet>
   <text:list-level-style-bullet text:level="9" text:style-name="Bullet_20_Symbols" text:bullet-char="▪">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="3in" fo:text-indent="-2.9902in" fo:margin-left="3in"/>
    </style:list-level-properties>
   </text:list-level-style-bullet>
   <text:list-level-style-bullet text:level="10" text:style-name="Bullet_20_Symbols" text:bullet-char="•">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="3.25in" fo:text-indent="-3.2402in" fo:margin-left="3.25in"/>
    </style:list-level-properties>
   </text:list-level-style-bullet>
  </text:list-style>
  <text:list-style style:name="L2">
   <text:list-level-style-number text:level="1" text:style-name="Numbering_20_Symbols" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="1in" fo:text-indent="-0.5in" fo:margin-left="1in"/>
    </style:list-level-properties>
   </text:list-level-style-number>
   <text:list-level-style-number text:level="2" text:style-name="Numbering_20_Symbols" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="1.25in" fo:text-indent="-0.25in" fo:margin-left="1.25in"/>
    </style:list-level-properties>
   </text:list-level-style-number>
   <text:list-level-style-number text:level="3" text:style-name="Numbering_20_Symbols" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="1.5in" fo:text-indent="-0.25in" fo:margin-left="1.5in"/>
    </style:list-level-properties>
   </text:list-level-style-number>
   <text:list-level-style-number text:level="4" text:style-name="Numbering_20_Symbols" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="1.75in" fo:text-indent="-0.25in" fo:margin-left="1.75in"/>
    </style:list-level-properties>
   </text:list-level-style-number>
   <text:list-level-style-number text:level="5" text:style-name="Numbering_20_Symbols" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="2in" fo:text-indent="-0.25in" fo:margin-left="2in"/>
    </style:list-level-properties>
   </text:list-level-style-number>
   <text:list-level-style-number text:level="6" text:style-name="Numbering_20_Symbols" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="2.25in" fo:text-indent="-0.25in" fo:margin-left="2.25in"/>
    </style:list-level-properties>
   </text:list-level-style-number>
   <text:list-level-style-number text:level="7" text:style-name="Numbering_20_Symbols" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="2.5in" fo:text-indent="-0.25in" fo:margin-left="2.5in"/>
    </style:list-level-properties>
   </text:list-level-style-number>
   <text:list-level-style-number text:level="8" text:style-name="Numbering_20_Symbols" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="2.75in" fo:text-indent="-0.25in" fo:margin-left="2.75in"/>
    </style:list-level-properties>
   </text:list-level-style-number>
   <text:list-level-style-number text:level="9" text:style-name="Numbering_20_Symbols" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="3in" fo:text-indent="-0.25in" fo:margin-left="3in"/>
    </style:list-level-properties>
   </text:list-level-style-number>
   <text:list-level-style-number text:level="10" text:style-name="Numbering_20_Symbols" style:num-format="">
    <style:list-level-properties text:list-level-position-and-space-mode="label-alignment">
     <style:list-level-label-alignment text:label-followed-by="listtab" text:list-tab-stop-position="3.25in" fo:text-indent="-0.25in" fo:margin-left="3.25in"/>
    </style:list-level-properties>
   </text:list-level-style-number>
  </text:list-style>
  <style:page-layout style:name="pm1">
   <style:page-layout-properties fo:page-width="8.5in" fo:page-height="11in" style:num-format="1" style:print-orientation="portrait" fo:margin-top="0in" fo:margin-bottom="0in" fo:margin-left="0in" fo:margin-right="0in" fo:background-color="#000000" style:writing-mode="lr-tb" draw:fill="solid" draw:fill-color="#000000" style:footnote-max-height="0in">
    <style:footnote-sep style:width="0.0071in" style:distance-before-sep="0.0398in" style:distance-after-sep="0.0398in" style:line-style="solid" style:adjustment="left" style:rel-width="25%" style:color="#000000"/>
   </style:page-layout-properties>
   <style:header-style/>
   <style:footer-style/>
  </style:page-layout>
 </office:automatic-styles>
 <office:master-styles>
  <style:master-page style:name="Standard" style:page-layout-name="pm1"/>
 </office:master-styles>
 <office:body>
  <office:text>
   <office:forms form:automatic-focus="false" form:apply-design-mode="false"/>
   <text:sequence-decls>
    <text:sequence-decl text:display-outline-level="0" text:name="Illustration"/>
    <text:sequence-decl text:display-outline-level="0" text:name="Table"/>
    <text:sequence-decl text:display-outline-level="0" text:name="Text"/>
    <text:sequence-decl text:display-outline-level="0" text:name="Drawing"/>
    <text:sequence-decl text:display-outline-level="0" text:name="Figure"/>
   </text:sequence-decls>
   <text:h text:style-name="Heading_20_1" text:outline-level="1">Name</text:h>
   <text:p text:style-name="Text_20_body">lexdiff - compare files lexically</text:p>
   <text:h text:style-name="Heading_20_1" text:outline-level="1">Synopsis</text:h>
   <text:list xml:id="list1102193797" text:style-name="L1">
    <text:list-item>
     <text:p text:style-name="P4">lexdiff -d dot-output specification-file</text:p>
    </text:list-item>
    <text:list-item>
     <text:p text:style-name="P4">lexdiff [-h]</text:p>
    </text:list-item>
    <text:list-item>
     <text:p text:style-name="P5">lexdiff [-v] [-p] specification-file before after</text:p>
    </text:list-item>
   </text:list>
   <text:h text:style-name="P1" text:outline-level="1">Description</text:h>
   <text:p text:style-name="Text_20_body"><text:span text:style-name="T7">A</text:span> line-by-line comparison can be too coarse for small differences and a character-by-character comparison too pedantic to be helpful; lexdiff attempts to reach a middle ground by essentially comparing the tokens (words) of the two files, similar to how humans read text. lexdiff provides a mechanism for the user to articulate the kinds of tokens lexdiff may encounter in the two files and the importance the differences between said tokens have. After the comparison, lexdiff will print a &quot;score&quot; to summarize the differences found.</text:p>
   <text:p text:style-name="P2">lexdiff scans for five kinds of differences: extra tokens (tokens present in after but not in before), missing tokens (tokens present in before but not in after), similar tokens (tokens matching the same regular-expression pattern, but do not consist of the same characters), exact matches (tokens consisting of the same characters), and tokens with numerical equality (tokens that when converted to a number have the same value (+/- some tolerance)). The way the score is affected (points lost or gained) by each difference depends on which token is missing, or extra, or exact, etc. For instance, missing keywords in a language may have a greater importance--and therefore a greater affect on the score--than, let&apos;s say, extra comments.</text:p>
   <text:p text:style-name="P2">lexdiff reads the specification file given on the command-line to know what tokens exist, and how the final score should be affected by differences their involved in.</text:p>
   <text:h text:style-name="Heading_20_1" text:outline-level="1">Specification file syntax</text:h>
   <text:p text:style-name="Text_20_body">The syntax of the specification file is made up of one or more token declarations, each token declaration consists of the regular expression for matching the token followed by a list of differences and the score loss or gain that would occur every time that kind of difference was detected. Example shown below:</text:p>
   <text:p text:style-name="Preformatted_20_Text">[<text:span text:style-name="T2">&apos;0&apos;</text:span>-<text:span text:style-name="T2">&apos;9&apos;</text:span>]+: {</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="4"/><text:span text:style-name="T3">extra</text:span>: -<text:span text:style-name="T5">10</text:span>,</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="4"/><text:span text:style-name="T3">similar</text:span>: -<text:span text:style-name="T5">5</text:span>,</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="4"/><text:span text:style-name="T3">exact</text:span>: <text:span text:style-name="T5">1</text:span> + <text:span text:style-name="T5">1</text:span>,</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="4"/><text:span text:style-name="T3">missing</text:span>: -<text:span text:style-name="T5">20</text:span>,</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="4"/><text:span text:style-name="T3">within</text:span> <text:span text:style-name="T5">1</text:span>%: -<text:span text:style-name="T5">1</text:span>,</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="4"/><text:span text:style-name="T3">within</text:span> <text:span text:style-name="T5">3</text:span>: -<text:span text:style-name="T5">2</text:span>,</text:p>
   <text:p text:style-name="Preformatted_20_Text">};</text:p>
   <text:h text:style-name="Heading_20_2" text:outline-level="2">Regular Expression Syntax</text:h>
   <text:p text:style-name="P2">The regular expression syntax has been modified a bit from what&apos;s conventional. This alternative syntax allows for better readability and makes it easy to introduce new operators without breaking old patterns. It could also be that I&apos;ve been looking at C code for too long and have gotten to the point where I don&apos;t like any syntax that doesn&apos;t remind me of C.</text:p>
   <text:p text:style-name="P2">Regardless: In order of operator precedence: vertical-bar (|) is the or/union operator, concatenation is done by juxtaposition, question mark (?), asterisk (*) and plus (+) are the 0-or-1, 0-or-more, and 1-or-more suffix operators respectively. Parenthesis can be used to change operator precedence. Including text in a pattern is done with C-style strings and character literals.</text:p>
   <text:p text:style-name="P2">Character sets can also be used in a regular-expression pattern, enclosed in square brackets ([]). The operators that can be used to define a character set are, in order of operator precedence: vertical bar (|) as the set-union operator, ampersand (&amp;) as the set-intersection operator, minus (-) as the range/span operator, and exclamation mark as the prefix set-complement operator. Parenthesis can be used to change operator precedence. Characters can included by C-style character literals.</text:p>
   <text:h text:style-name="Heading_20_1" text:outline-level="1">COMMAND LINE OPTIONS</text:h>
   <text:list xml:id="list2625132723" text:style-name="L2">
    <text:list-item>
     <text:p text:style-name="P3">-d output</text:p>
    </text:list-item>
    <text:list-item>
     <text:p text:style-name="P3">--dotout output</text:p>
     <text:list>
      <text:list-item>
       <text:p text:style-name="P3">This flag disables file comparison. Instead lexdiff will output the tokenizer state machine as a Graphviz dot-file. This is mostly useful for debugging lexdiff.</text:p>
      </text:list-item>
     </text:list>
    </text:list-item>
    <text:list-item>
     <text:p text:style-name="P3">-h</text:p>
    </text:list-item>
    <text:list-item>
     <text:p text:style-name="P3">--help</text:p>
     <text:list>
      <text:list-item>
       <text:p text:style-name="P6"><text:span text:style-name="T1">This flag causes lexdiff to print a usage message and quit</text:span></text:p>
      </text:list-item>
     </text:list>
    </text:list-item>
    <text:list-item>
     <text:p text:style-name="P3">-p</text:p>
    </text:list-item>
    <text:list-item>
     <text:p text:style-name="P3">--pretty-print</text:p>
     <text:list>
      <text:list-item>
       <text:p text:style-name="P3">This flag causes lexdiff to print to the terminal the tokens read from both files, with tokens marked green if they were present in file-b but not file-a (extra), red if present in file-a but not file-b (missing), yellow if present in both files but with different characters (similar), and grey if present and same characters (exact). Line numbers are also printed for file-a and file-b respectively. This flag is disabled by default.</text:p>
      </text:list-item>
     </text:list>
    </text:list-item>
    <text:list-item>
     <text:p text:style-name="P3">-v</text:p>
    </text:list-item>
    <text:list-item>
     <text:p text:style-name="P3">--verbose</text:p>
     <text:list>
      <text:list-item>
       <text:p text:style-name="P3">Currently silently ignored.</text:p>
      </text:list-item>
     </text:list>
    </text:list-item>
   </text:list>
   <text:h text:style-name="Heading_20_1" text:outline-level="1">EXAMPLES</text:h>
   <text:p text:style-name="P2">For an example, let&apos;s say there are two files listing kinds of fruit. Whitespace doesn&apos;t matter, and &apos;onions&apos; is especially important to keep. The specification file is given below:</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:span text:style-name="T9">// ignore whitespace:</text:span><text:line-break/><text:span text:style-name="T2">&apos; &apos;</text:span> | <text:span text:style-name="T2">&apos;\t&apos;</text:span> | <text:span text:style-name="T2">&apos;\n&apos;</text:span>: {};</text:p>
   <text:p text:style-name="Preformatted_20_Text"/>
   <text:p text:style-name="Preformatted_20_Text"><text:span text:style-name="T9">// commas matter very little:</text:span><text:line-break/><text:span text:style-name="T2">&apos;,&apos;</text:span>: { <text:span text:style-name="T3">extra</text:span>: <text:span text:style-name="T4">-1</text:span>, <text:span text:style-name="T3">missing</text:span>: <text:span text:style-name="T4">-1</text:span> };</text:p>
   <text:p text:style-name="Preformatted_20_Text"/>
   <text:p text:style-name="Preformatted_20_Text"><text:span text:style-name="T9">// fruit are only somewhat important</text:span><text:line-break/>[<text:span text:style-name="T2">&apos;a&apos;</text:span>-<text:span text:style-name="T2">&apos;z&apos;</text:span>|<text:span text:style-name="T2">&apos;A&apos;</text:span>-<text:span text:style-name="T2">&apos;Z&apos;</text:span>]+: {<text:line-break/> <text:s text:c="3"/><text:span text:style-name="T3">extra</text:span> <text:s/>: <text:span text:style-name="T4">-20</text:span>,<text:line-break/> <text:s text:c="3"/><text:span text:style-name="T3">similar</text:span>: <text:span text:style-name="T4">-5</text:span>,<text:line-break/> <text:s text:c="3"/><text:span text:style-name="T3">missing</text:span>: <text:span text:style-name="T4">-20</text:span>,<text:line-break/>};</text:p>
   <text:p text:style-name="Preformatted_20_Text"/>
   <text:p text:style-name="Preformatted_20_Text"><text:span text:style-name="T9">// but onions are really important</text:span><text:line-break/><text:span text:style-name="T2">&quot;onions&quot;</text:span>: {<text:line-break/><text:tab/><text:span text:style-name="T3">missing</text:span>: <text:span text:style-name="T4">-50</text:span>,<text:line-break/>};</text:p>
   <text:p text:style-name="P8"/>
   <text:p text:style-name="Text_20_body">Running lexdiff on these two input files would yield the output:</text:p>
   <text:p text:style-name="Preformatted_20_Text">$ cat before.txt</text:p>
   <text:p text:style-name="Preformatted_20_Text">apples,bananas,peaches</text:p>
   <text:p text:style-name="Preformatted_20_Text">dragonfruit,grapefruit</text:p>
   <text:p text:style-name="Preformatted_20_Text">grapes,onions</text:p>
   <text:p text:style-name="Preformatted_20_Text"/>
   <text:p text:style-name="Preformatted_20_Text">$ cat after.txt</text:p>
   <text:p text:style-name="Preformatted_20_Text">apples, bananas, peaches</text:p>
   <text:p text:style-name="Preformatted_20_Text">dragoonfruit</text:p>
   <text:p text:style-name="Preformatted_20_Text">grapefruit</text:p>
   <text:p text:style-name="Preformatted_20_Text">, onions</text:p>
   <text:p text:style-name="Preformatted_20_Text"/>
   <text:p text:style-name="Preformatted_20_Text">$ lexdiff -p fruit.ldiff before.txt after.txt</text:p>
   <text:p text:style-name="Preformatted_20_Text">score: 74</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="2"/>1/ <text:s/>1 | apples,_bananas,_peaches <text:s text:c="4"/>| extra &apos;_&apos; (0)</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="40"/>| extra &apos;_&apos; (0)</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="2"/>2/ <text:s/>2 | dragoonfruit <text:s text:c="16"/>| &apos;dragonfruit&apos; instead of &apos;dragoonfruit&apos; (-5)</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="40"/>| extra &apos;&apos; (0)</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="2"/>2/ <text:s/>3 | ,grapefruit <text:s text:c="17"/>| missing &apos;,&apos; (-1)</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="2"/>3/ <text:s/>4 | grapes,_onions <text:s text:c="14"/>| missing &apos;grapes&apos; (-20)</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="40"/>| extra &apos;_&apos; (0)</text:p>
   <text:p text:style-name="Preformatted_20_Text"><text:s text:c="2"/>4/ <text:s/>5 | </text:p>
   <text:p text:style-name="P7"/>
   <text:p text:style-name="P7">The final score is 74 because &apos;dragonfruit&apos; is misspelled (-5 points), the comma between &apos;dragonfruit&apos; and &apos;grapefruit&apos; was removed (-1 point) and &apos;grapes&apos; is missing (-20 points). 100 - 5 - 1 - 20 = 74.</text:p>
   <text:h text:style-name="Heading_20_1" text:outline-level="1">BUILDING</text:h>
   <text:p text:style-name="Text_20_body">The source code for lexdiff can be found on its Github page. Building lexdiff is fairly simple, run &apos;make&apos; to build and &apos;make install&apos; to install. Lexdiff depends on the GNU Multiple Precision Arithmetic Library (GMP) on compile time, so make sure that&apos;s installed first! On Ubuntu, this can be installed with the command &apos;sudo apt install libgmp-dev&apos;. The installation prefix defaults to ${HOME}/bin, this can be changed by setting it in the call to make: &apos;make install PREFIX=/something/else&apos;.</text:p>
   <text:h text:style-name="Heading_20_1" text:outline-level="1">NOTES</text:h>
   <text:h text:style-name="Heading_20_2" text:outline-level="2">The Tokenizer</text:h>
   <text:p text:style-name="P7">It is worth noting that lexdiff&apos;s tokenization is greedy, meaning that it will always try to put characters into the largest token it can.</text:p>
   <text:p text:style-name="P7">Sometimes a string could be identified as either one token or another, lexdiff will resolve this ambiguity by using the token declared later in the specification file.</text:p>
   <text:h text:style-name="Heading_20_1" text:outline-level="1">AUTHOR</text:h>
   <text:p text:style-name="Text_20_body">Written by Alexander Thannhauser.</text:p>
   <text:h text:style-name="Heading_20_1" text:outline-level="1">REPORTING BUGS</text:h>
   <text:p text:style-name="Text_20_body">Report bugs to: <text:a xlink:type="simple" xlink:href="mailto:zthannhauser@gmail.com" text:style-name="Internet_20_link" text:visited-style-name="Visited_20_Internet_20_Link">zthannhauser@gmail.com</text:a>.</text:p>
   <text:h text:style-name="Heading_20_1" text:outline-level="1">SEE ALSO</text:h>
   <text:p text:style-name="Text_20_body"/>
  </office:text>
 </office:body>
</office:document>
""");

run(["/tmp/flat-odt", "/tmp/man-lexdiff.txt"]);


































