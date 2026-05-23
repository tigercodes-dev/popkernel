#    PopKernel OS Makefile for generated media
#    Copyright (C) 2026  tigercodes-dev
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.

.PHONY: iso-x86_64 iso-x86_64-files iso-x86_64-clean

iso-x86_64: iso-x86_64-files
	@echo "Creating ISO with grub-mkrescue..."
	grub-mkrescue -o $(ROOTDIR)/$(CONFIG_ISO_OUTPUT) -V $(CONFIG_ISO_VOLUME_NAME) $(ISOROOT)

iso-x86_64-files: $(ISOROOT)/boot/pkrnl.kb0

$(ISOROOT)/boot/pkrnl.kb0: $(DISTDIR)/x86_64-pkrnl.kb0.bin
	@install -d -m 755 $(@D)
	@install -m 644 $< $@
	@echo "  INSTALL $< --> $@."

iso-x86_64-clean:
	rm -f $(ISOROOT)/boot/pkrnl.kb*
