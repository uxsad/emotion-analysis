========
emotions
========

-------------------------
An interface to Affectiva
-------------------------

:Author: Andrea Esposito <a.esposito39@studenti.uniba.it>
:Version: 1.0.0
:Date: 2020-11-11
:Manual section: 1
:Manual group: UX-SAD

Synopsis
========

**emotions** [*OPTIONS* ...] *IMAGE*...

**emotions** [*OPTIONS* ...] **--file** *FILE*

Description
===========

This program analyzes the facial expressions in a photo in order to extract
data on the emotions represented in the picture.

This tool extract the same seven emotions recognized as "universal" by Paul
Ekman (**anger**, **contempt**, **disgust**, **fear**, **joy**, **sadness**,
**surprise**) alongside two additional useful values: the **engagement** (a
measure of the facial muscle activation illustrating the subject expressiveness)
and the **valence** (a measure of the positive/negative nature of the
experience). All the emotions span in a range from 0 to 100 (inclusive) with the
only exception being the valence, that spans in a range from -100 to 100
(inclusive).

Options
=======

-h, --help             Display an help message

-f FILE, --file FILE   The file containing the images to be analyzed, expressed
                       as data URIs.

Notes
=====

There are some known limitations that should be taken into account when using
**emotions**.

- Due to some issues in the Affectiva SDK, **emotions** is only available on
  Windows and Ubuntu 16.04 (LTS). On any other operative system, the
  functionalities are not guaranteed.
- Due to some issues in the Affectiva SDK, **emotions** may not terminate with a
  0 code even if no errors occurred. But, in general, if some output is written
  to **stdout** then no errors occurred.
- The images analyzed by **emotions** should contain at most one face. If more
  than one face is present, only one (randomly chosen) of them will be analyzed
  to obtain the emotions data.

Copyright
=========

| Copyright (C) 2020 Andrea Esposito.
| License GPLv3+: GNU GPL version 3 or Later <https://gnu.org/licenses/gpl.html>.

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
