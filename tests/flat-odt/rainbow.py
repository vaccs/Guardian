
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

with open("/tmp/rainbow.txt", "w") as stream:
    stream.write("""
<?xml version="1.0" encoding="UTF-8"?>

<office:document xmlns:officeooo="http://openoffice.org/2009/office" xmlns:css3t="http://www.w3.org/TR/css3-text/" xmlns:grddl="http://www.w3.org/2003/g/data-view#" xmlns:xhtml="http://www.w3.org/1999/xhtml" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:chart="urn:oasis:names:tc:opendocument:xmlns:chart:1.0" xmlns:svg="urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0" xmlns:draw="urn:oasis:names:tc:opendocument:xmlns:drawing:1.0" xmlns:rpt="http://openoffice.org/2005/report" xmlns:text="urn:oasis:names:tc:opendocument:xmlns:text:1.0" xmlns:style="urn:oasis:names:tc:opendocument:xmlns:style:1.0" xmlns:meta="urn:oasis:names:tc:opendocument:xmlns:meta:1.0" xmlns:config="urn:oasis:names:tc:opendocument:xmlns:config:1.0" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:fo="urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0" xmlns:of="urn:oasis:names:tc:opendocument:xmlns:of:1.2" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:ooo="http://openoffice.org/2004/office" xmlns:dr3d="urn:oasis:names:tc:opendocument:xmlns:dr3d:1.0" xmlns:formx="urn:openoffice:names:experimental:ooxml-odf-interop:xmlns:form:1.0" xmlns:calcext="urn:org:documentfoundation:names:experimental:calc:xmlns:calcext:1.0" xmlns:drawooo="http://openoffice.org/2010/draw" xmlns:field="urn:openoffice:names:experimental:ooo-ms-interop:xmlns:field:1.0" xmlns:office="urn:oasis:names:tc:opendocument:xmlns:office:1.0" xmlns:table="urn:oasis:names:tc:opendocument:xmlns:table:1.0" xmlns:number="urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0" xmlns:ooow="http://openoffice.org/2004/writer" xmlns:oooc="http://openoffice.org/2004/calc" xmlns:tableooo="http://openoffice.org/2009/table" xmlns:loext="urn:org:documentfoundation:names:experimental:office:xmlns:loext:1.0" xmlns:math="http://www.w3.org/1998/Math/MathML" xmlns:form="urn:oasis:names:tc:opendocument:xmlns:form:1.0" xmlns:script="urn:oasis:names:tc:opendocument:xmlns:script:1.0" xmlns:dom="http://www.w3.org/2001/xml-events" xmlns:xforms="http://www.w3.org/2002/xforms" office:version="1.2" office:mimetype="application/vnd.oasis.opendocument.text">
 <office:meta><meta:creation-date>2023-05-15T07:20:25.880178893</meta:creation-date><dc:date>2023-05-15T07:38:22.822363543</dc:date><meta:editing-duration>PT17M58S</meta:editing-duration><meta:editing-cycles>1</meta:editing-cycles><meta:document-statistic meta:table-count="0" meta:image-count="1" meta:object-count="0" meta:page-count="1" meta:paragraph-count="4" meta:word-count="12" meta:character-count="69" meta:non-whitespace-character-count="61"/><meta:generator>LibreOffice/6.4.7.2$Linux_X86_64 LibreOffice_project/40$Build-2</meta:generator></office:meta>
 <office:settings>
  <config:config-item-set config:name="ooo:view-settings">
   <config:config-item config:name="ViewAreaTop" config:type="long">44</config:config-item>
   <config:config-item config:name="ViewAreaLeft" config:type="long">0</config:config-item>
   <config:config-item config:name="ViewAreaWidth" config:type="long">33341</config:config-item>
   <config:config-item config:name="ViewAreaHeight" config:type="long">16923</config:config-item>
   <config:config-item config:name="ShowRedlineChanges" config:type="boolean">true</config:config-item>
   <config:config-item config:name="InBrowseMode" config:type="boolean">false</config:config-item>
   <config:config-item-map-indexed config:name="Views">
    <config:config-item-map-entry>
     <config:config-item config:name="ViewId" config:type="string">view2</config:config-item>
     <config:config-item config:name="ViewLeft" config:type="long">11700</config:config-item>
     <config:config-item config:name="ViewTop" config:type="long">9624</config:config-item>
     <config:config-item config:name="VisibleLeft" config:type="long">0</config:config-item>
     <config:config-item config:name="VisibleTop" config:type="long">44</config:config-item>
     <config:config-item config:name="VisibleRight" config:type="long">33339</config:config-item>
     <config:config-item config:name="VisibleBottom" config:type="long">16965</config:config-item>
     <config:config-item config:name="ZoomType" config:type="short">0</config:config-item>
     <config:config-item config:name="ViewLayoutColumns" config:type="short">1</config:config-item>
     <config:config-item config:name="ViewLayoutBookMode" config:type="boolean">false</config:config-item>
     <config:config-item config:name="ZoomFactor" config:type="short">140</config:config-item>
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
   <config:config-item config:name="Rsid" config:type="int">1684442</config:config-item>
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
   <config:config-item config:name="RsidRoot" config:type="int">1684442</config:config-item>
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
   <ooo:libraries xmlns:ooo="http://openoffice.org/2004/office" xmlns:xlink="http://www.w3.org/1999/xlink"/>
  </office:script>
 </office:scripts>
 <office:font-face-decls>
  <style:font-face style:name="Lohit Devanagari1" svg:font-family="&apos;Lohit Devanagari&apos;"/>
  <style:font-face style:name="Liberation Serif" svg:font-family="&apos;Liberation Serif&apos;" style:font-family-generic="roman" style:font-pitch="variable"/>
  <style:font-face style:name="Liberation Sans" svg:font-family="&apos;Liberation Sans&apos;" style:font-family-generic="swiss" style:font-pitch="variable"/>
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
  <style:style style:name="Standard" style:family="paragraph" style:class="text"/>
  <style:style style:name="Heading" style:family="paragraph" style:parent-style-name="Standard" style:next-style-name="Text_20_body" style:class="text">
   <style:paragraph-properties fo:margin-top="0.1665in" fo:margin-bottom="0.0835in" loext:contextual-spacing="false" fo:keep-with-next="always"/>
   <style:text-properties style:font-name="Liberation Sans" fo:font-family="&apos;Liberation Sans&apos;" style:font-family-generic="swiss" style:font-pitch="variable" fo:font-size="14pt" style:font-name-asian="Noto Sans CJK SC" style:font-family-asian="&apos;Noto Sans CJK SC&apos;" style:font-family-generic-asian="system" style:font-pitch-asian="variable" style:font-size-asian="14pt" style:font-name-complex="Lohit Devanagari" style:font-family-complex="&apos;Lohit Devanagari&apos;" style:font-family-generic-complex="system" style:font-pitch-complex="variable" style:font-size-complex="14pt"/>
  </style:style>
  <style:style style:name="Text_20_body" style:display-name="Text body" style:family="paragraph" style:parent-style-name="Standard" style:class="text">
   <style:paragraph-properties fo:margin-top="0in" fo:margin-bottom="0.0972in" loext:contextual-spacing="false" fo:line-height="115%"/>
  </style:style>
  <style:style style:name="List" style:family="paragraph" style:parent-style-name="Text_20_body" style:class="list">
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
  <style:style style:name="Figure" style:family="paragraph" style:parent-style-name="Caption" style:class="extra"/>
  <style:style style:name="Header_20_and_20_Footer" style:display-name="Header and Footer" style:family="paragraph" style:parent-style-name="Standard" style:class="extra">
   <style:paragraph-properties text:number-lines="false" text:line-number="0">
    <style:tab-stops>
     <style:tab-stop style:position="3.3555in" style:type="center"/>
     <style:tab-stop style:position="6.711in" style:type="right"/>
    </style:tab-stops>
   </style:paragraph-properties>
  </style:style>
  <style:style style:name="Header" style:family="paragraph" style:parent-style-name="Header_20_and_20_Footer" style:class="extra">
   <style:paragraph-properties text:number-lines="false" text:line-number="0">
    <style:tab-stops>
     <style:tab-stop style:position="3.3555in" style:type="center"/>
     <style:tab-stop style:position="6.711in" style:type="right"/>
    </style:tab-stops>
   </style:paragraph-properties>
  </style:style>
  <style:style style:name="Footer" style:family="paragraph" style:parent-style-name="Header_20_and_20_Footer" style:class="extra">
   <style:paragraph-properties text:number-lines="false" text:line-number="0">
    <style:tab-stops>
     <style:tab-stop style:position="3.3555in" style:type="center"/>
     <style:tab-stop style:position="6.711in" style:type="right"/>
    </style:tab-stops>
   </style:paragraph-properties>
  </style:style>
  <style:style style:name="Graphics" style:family="graphic">
   <style:graphic-properties text:anchor-type="paragraph" svg:x="0in" svg:y="0in" style:wrap="dynamic" style:number-wrapped-paragraphs="no-limit" style:wrap-contour="false" style:vertical-pos="top" style:vertical-rel="paragraph" style:horizontal-pos="center" style:horizontal-rel="paragraph"/>
  </style:style>
  <style:style style:name="Frame" style:family="graphic">
   <style:graphic-properties text:anchor-type="paragraph" svg:x="0in" svg:y="0in" fo:margin-left="0.0791in" fo:margin-right="0.0791in" fo:margin-top="0.0791in" fo:margin-bottom="0.0791in" style:wrap="parallel" style:number-wrapped-paragraphs="no-limit" style:wrap-contour="false" style:vertical-pos="top" style:vertical-rel="paragraph-content" style:horizontal-pos="center" style:horizontal-rel="paragraph-content" fo:padding="0.0591in" fo:border="0.06pt solid #000000"/>
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
  <style:style style:name="P1" style:family="paragraph" style:parent-style-name="Header">
   <style:text-properties officeooo:rsid="0019b3da" officeooo:paragraph-rsid="0019b3da"/>
  </style:style>
  <style:style style:name="P2" style:family="paragraph" style:parent-style-name="Footer">
   <style:text-properties officeooo:rsid="0019b3da" officeooo:paragraph-rsid="0019b3da"/>
  </style:style>
  <style:style style:name="P3" style:family="paragraph" style:parent-style-name="Footer">
   <style:text-properties officeooo:rsid="0019b3da" officeooo:paragraph-rsid="0019b3da"/>
  </style:style>
  <style:style style:name="P4" style:family="paragraph" style:parent-style-name="Header">
   <style:text-properties officeooo:rsid="0019b3da" officeooo:paragraph-rsid="0019b3da"/>
  </style:style>
  <style:style style:name="P5" style:family="paragraph" style:parent-style-name="Standard" style:master-page-name="">
   <loext:graphic-properties draw:fill="none"/>
   <style:paragraph-properties fo:margin-left="-0.1252in" fo:margin-right="0in" fo:text-indent="0in" style:auto-text-indent="false" style:page-number="auto" fo:background-color="transparent"/>
   <style:text-properties officeooo:rsid="0019b3da" officeooo:paragraph-rsid="0019b3da"/>
  </style:style>
  <style:style style:name="fr1" style:family="graphic" style:parent-style-name="Frame">
   <style:graphic-properties fo:margin-left="0in" fo:margin-right="0in" fo:margin-top="0in" fo:margin-bottom="0in" style:wrap="dynamic" style:number-wrapped-paragraphs="no-limit" style:vertical-pos="from-top" style:vertical-rel="paragraph" style:horizontal-pos="from-left" style:horizontal-rel="paragraph" fo:padding="0in" fo:border="none"/>
  </style:style>
  <style:style style:name="fr2" style:family="graphic" style:parent-style-name="Graphics">
   <style:graphic-properties fo:margin-left="0in" fo:margin-right="0in" fo:margin-top="0in" fo:margin-bottom="0in" style:run-through="foreground" style:wrap="none" style:vertical-pos="top" style:vertical-rel="paragraph-content" style:horizontal-pos="center" style:horizontal-rel="paragraph-content" fo:padding="0in" fo:border="none" style:shadow="none" draw:shadow-opacity="100%" style:mirror="none" fo:clip="rect(0in, 0in, 0in, 0in)" draw:luminance="0%" draw:contrast="0%" draw:red="0%" draw:green="0%" draw:blue="0%" draw:gamma="100%" draw:color-inversion="false" draw:image-opacity="100%" draw:color-mode="standard" draw:wrap-influence-on-position="once-concurrent" loext:allow-overlap="true" loext:rel-width-rel="paragraph"/>
  </style:style>
  <style:page-layout style:name="pm1">
   <style:page-layout-properties fo:page-width="8.5in" fo:page-height="11in" style:num-format="1" style:print-orientation="portrait" fo:margin-top="0.7874in" fo:margin-bottom="0.7874in" fo:margin-left="1.0016in" fo:margin-right="0.7874in" style:writing-mode="lr-tb" style:footnote-max-height="0in">
    <style:footnote-sep style:width="0.0071in" style:distance-before-sep="0.0398in" style:distance-after-sep="0.0398in" style:line-style="solid" style:adjustment="left" style:rel-width="25%" style:color="#000000"/>
   </style:page-layout-properties>
   <style:header-style>
    <style:header-footer-properties fo:min-height="0in" fo:margin-bottom="0.1965in"/>
   </style:header-style>
   <style:footer-style>
    <style:header-footer-properties fo:min-height="0in" fo:margin-top="0.1965in"/>
   </style:footer-style>
  </style:page-layout>
 </office:automatic-styles>
 <office:master-styles>
  <style:master-page style:name="Standard" style:page-layout-name="pm1">
   <style:header>
    <text:p text:style-name="P1">Header (Page <text:page-number text:select-page="current">1</text:page-number>)</text:p>
   </style:header>
   <style:footer>
    <text:p text:style-name="P2">Footer</text:p>
   </style:footer>
  </style:master-page>
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
   <text:p text:style-name="P5"><draw:frame draw:style-name="fr1" draw:name="Frame1" text:anchor-type="char" svg:x="0.7862in" svg:y="0.1756in" svg:width="1.111in" draw:z-index="0">
     <draw:text-box fo:min-height="1.111in">
      <text:p text:style-name="Figure">Figure <text:sequence text:ref-name="refFigure0" text:name="Figure" text:formula="ooow:Figure+1" style:num-format="1">1</text:sequence>: You know what you did</text:p>
     </draw:text-box>
    </draw:frame>ddddddddddddddddd<draw:frame draw:style-name="fr2" draw:name="my favorate image" text:anchor-type="char" svg:width="2.3874in" style:rel-width="36%" svg:height="2.3874in" style:rel-height="scale" draw:z-index="1"><draw:image loext:mime-type="image/x-MS-bmp">
      <office:binary-data>Qk16AwAAAAAAAHoAAABsAAAAEAAAABAAAAABABgAAAAAAAADAAAjLgAAIy4AAAAAAAAAAAAA
       QkdScwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAIA
       AAAAAAAAAAAAAAAAAAAAAP8AT/8Afv8Apv8A3f8A//IA/8oA/6MA/1QS/wCJ/wDI/wD/5wD/
       kQD/iQD/UQAAAAAAAP8AT/8Afv8Apv8A3f8A//IA/8oA/6MA/1QS/wCJ/wDI/wD/5wD/kQD/
       iQAAAAAaGhoAAP8AT/8Afv8Apv8A3f8A//IA/8oA/6MA/1QS/wCJ/wDI/wD/5wD/kQAAAAAa
       GholJSUAAP8AT/8Afv8Apv8A3f8A//IA/8oA/6MA/1QS/wCJ/wDI/wD/5wAAAAAaGholJSUv
       Ly8AAP8AT/8Afv8Apv8A3f8A//IA/8oA/6MA/1QS/wCJ/wDI/wAAAAAaGholJSUvLy9MTEwA
       AP8AT/8Afv8Apv8A3f8A//IA/8oA/6MA/1QS/wCJ/wAAAAAaGholJSUvLy9MTExpaWkAAP8A
       T/8Afv8Apv8A3f8A//IA/8oA/6MA/1QS/wAAAAAaGholJSUvLy9MTExpaWl4eHgAAP8AT/8A
       fv8Apv8A3f8A//IA/8oA/6MA/1QAAAAaGholJSUvLy9MTExpaWl4eHiAgIAAAP8AT/8Afv8A
       pv8A3f8A//IA/8oA/6MAAAAaGholJSUvLy9MTExpaWl4eHiAgICPj48AAP8AT/8Afv8Apv8A
       3f8A//IA/8oAAAAaGholJSUvLy9MTExpaWl4eHiAgICPj4+fn58AAP8AT/8Afv8Apv8A3f8A
       //IAAAAaGholJSUvLy9MTExpaWl4eHiAgICPj4+fn5+vr68AAP8AT/8Afv8Apv8A3f8AAAAa
       GholJSUvLy9MTExpaWl4eHiAgICPj4+fn5+vr6/AwMAAAP8AT/8Afv8Apv8AAAAaGholJSUv
       Ly9MTExpaWl4eHiAgICPj4+fn5+vr6/AwMDY2NgAAP8AT/8Afv8AAAAaGholJSUvLy9MTExp
       aWl4eHiAgICPj4+fn5+vr6/AwMDY2Njh4eEAAP8AT/8AAAAaGholJSUvLy9MTExpaWl4eHiA
       gICPj4+fn5+vr6/AwMDY2Njh4eH///8AAP8=
      </office:binary-data>
     </draw:image>
    </draw:frame></text:p>
  </office:text>
 </office:body>
</office:document>
""");

run(["/tmp/flat-odt", "/tmp/rainbow.txt"]);


































