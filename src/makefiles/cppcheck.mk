CPPCHECK_FLAGS=--enable=all --language=c --std=c11

_cppcheck:
	cppcheck $(CPPCHECK_FLAGS) .

# Используется для принудительного анализа всех возможных конфигураций предварительной обработки.
_cppcheck_force:
	$(eval CPPCHECK_FLAGS += --force)

# Используется для подавления предупреждений о системных заголовочных файлах, которые не найдены во время анализа.
_cppcheck_suppress:
	$(eval CPPCHECK_FLAGS += --suppress=missingIncludeSystem)

# Используется для включения предупреждений о потенциальных проблемах, которые не могут быть однозначно определены.
_cppcheck_inconclusive:
	$(eval CPPCHECK_FLAGS += --inconclusive)

# Позволяет автоматическим системам CI обнаружить наличие проблем.
_cppcheck_ci:
	$(eval CPPCHECK_FLAGS += --error-exitcode=1)

# Включить текущую директорию для поиска заголовочных файлов.
_cppcheck_h:
	$(eval CPPCHECK_FLAGS += -I .)

# Сохранить вывод анализа в файл
_cppcheck_xml:
	$(eval CPPCHECK_FLAGS += --xml-version=2 --output-file=report/cppcheck.xml)

# Выведет информацию о любых проблемах в конфигурации, которые могут мешать анализу.
_cppcheck_config:
	$(eval CPPCHECK_FLAGS += --check-config .)

test-cppcheck: _cppcheck_force _cppcheck_inconclusive _cppcheck_h _cppcheck_suppress _cppcheck

test-cppcheck_ci: _cppcheck_ci test-cppcheck

test-cppcheck_html: _dir-report _cppcheck_force _cppcheck_inconclusive _cppcheck_h _cppcheck_suppress _cppcheck_xml _cppcheck
	cppcheck-htmlreport --file=report/cppcheck.xml --report-dir=report/cppcheck --source-dir=.
